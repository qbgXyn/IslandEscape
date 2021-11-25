#include "Ghost.h"
#include "../../Map/Map.h"

// for simplicity, no collsion means we don't need any algorithm for path finding
const float Ghost::base_collison_radius = 0.0;

const double Ghost::base_max_speed = 20.0;
const float Ghost::base_attackInterval = 3.0;
const float Ghost::base_attack_radius = 16.0;

const double patrolRadius = 256.0;
const double chasingRadius = 640.0;


Ghost::Ghost(Map *map, double x, double y, Unit *chasing_target) : Unit(map, x, y) {
    type = Handle::Type::GHOST;
    this->chasing_target = chasing_target;
    patrolCenterLocation[0] = x;
    patrolCenterLocation[1] = y;
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    pathable += Terrain::Type::SHOAL;
    pathable += Terrain::Type::OCEAN;
    pathable += Terrain::Type::VOID;
}

// void Ghost::attack() {
// //set attack interval of ghost

//     auto t_start = std::chrono::high_resolution_clock::now();

//     vector<Handle*> list = map->getHandleGroup(location[0], location[1], base_attack_radius); // get all surrounding handle within attack radius

//     vector<Handle*>::const_iterator it_end = list.end(); 
//     for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) 
//     {
//         if (isInsideSector(*it, base_attack_sector_angle) == true) // check if it within attack sector range
//         {
//             if (!isInvulnerable()) //check if it is vulnerable
//             {
//                 if ((*it) -> getType() == Handle::Type::SURVIVOR) // check if it is Unit
//                 {
//                     if (this -> getDamage() >= (*it) -> getArmor()) // check if attack > armor
//                     {
//                         int newHealth = this -> getHealth() - (this -> getDamage() - (*it) -> getArmor());
//                         this -> setHealth(newHealth);
//                     }
//                 }
//             }
//         }

//     }
//     while (true)
//     {
//     auto t_end = std::chrono::high_resolution_clock::now();
//     if (std::chrono::duration<float, milli>(t_end - t_start).count() > 1 / base_attackInterval)
//     {
//     //cout << chrono::duration<float, milli>(t_end - t_start).count() << endl;
//      break;
//     }
//     }

// }


void Ghost::patrol() {
    double x;
    double y;
    while(true) {
        x = map->getRandomLocation(location[0] - patrolRadius, location[0] + patrolRadius);
        y = map->getRandomLocation(location[1] - patrolRadius, location[1] + patrolRadius);
        if (std::hypot(x, y) <= patrolRadius) {
            break;
        }
    }
    move_AI(x, y);

}


void Ghost::move_AI(double x, double y) {
    double dx = abs(x - location[0]);
    double dy = abs(y - location[1]);
    double total = dx+dy;

    // separate max_speed to x and y components by ratio
    velocity[0] = dx/total * max_speed;
    velocity[1] = dy/total * max_speed;
}

void Ghost::chase(Unit* u) {
    double d = std::hypot(location[0] - patrolCenterLocation[0], location[1] - location[0]);
    if (d > chasingRadius) {
        move_AI(patrolCenterLocation[0], patrolCenterLocation[1]);
    }else {
        if (map->distanceBetweenPoints(location[0], location[1], u->getX(), u->getY()) < base_attack_radius) {
            attack(base_attack_radius, base_attack_sector_angle, base_attackInterval);
        }
        move_AI(u->getX(), u->getY());
    }
}