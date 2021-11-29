#include "Ghost.h"
#include "../../Map/Map.h"

// for simplicity, no collsion means we don't need any algorithm for path finding
const float Ghost::base_collison_radius = 0.0;

const double Ghost::base_max_speed = 20.0; //base maximum speed
const int Ghost::base_attackInterval = 3*GAME_TICK; //base attack CD
const float Ghost::base_attack_radius = 16.0; //base attack radius
const double Ghost::base_attack_sector_angle = 60.0; //base attack circular angle sector

const double Ghost::patrolRadius = 256.0; //patrol radius of ghost 
const double Ghost::detectRadius = 400.0; //detect player radius
const double Ghost::chasingRadius = 800.0; //chasing radius


Ghost::Ghost(Map *map, double x, double y, Handle *chasing_target) : Unit(map, x, y) { //ghost constructor
    type = Handle::Type::GHOST;
    this->chasing_target = chasing_target;
    patrolCenterLocation[0] = x;
    patrolCenterLocation[1] = y;
    //ghost can walk on all area of the map, include the ocean which player cannot
    // so in this way we don't need any algorithm for path finding
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    pathable += Terrain::Type::SHOAL;
    pathable += Terrain::Type::OCEAN;
    pathable += Terrain::Type::VOID; 

    // initially no attack cooldown
    attack_cooldown = 0;

    visible_size = base_visible_size;
    health = base_max_health;
    damage = base_damage;
    armor = base_armor; //initalise base value
}

void Ghost::infoUpdate() {
    if (attack_cooldown > 0) {
        --attack_cooldown;
    }
}

void Ghost::patrol() {
    double x;
    double y;
    while(true) {
        x = map->getRandomLocation(location[0] - patrolRadius, location[0] + patrolRadius);
        y = map->getRandomLocation(location[1] - patrolRadius, location[1] + patrolRadius);
        if (std::hypot(x, y) <= patrolRadius) { //randomly walk within the patrol radius
            break;
        }
    }
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], detectRadius); // get all surrounding handle within attack radius

    vector<Handle*>::const_iterator it_end = list.end(); 
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) {
        if ((*it)->getType() == Handle::Type::SURVIVOR) {
            chasing_target = *it;
            return; //if within the detect radius has survivor, start chasing
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

void Ghost::ai() {
    if (chasing_target) {
        chase(chasing_target);
    }else if (velocity[0] <= ECLIPSE && velocity[0] >= -ECLIPSE && velocity[1] <= ECLIPSE && velocity[1] >= -ECLIPSE) {     // if velocity is 0, i.e ghost is static
        patrol();
    }
}

void Ghost::chase(Handle* u) {
    double d = std::hypot(location[0] - patrolCenterLocation[0], location[1] - location[0]);
    if (d > chasingRadius || !isHandleVisible(u)) {
        move_AI(patrolCenterLocation[0], patrolCenterLocation[1]);
        chasing_target = nullptr;
    }else {
        if (map->distanceBetweenPoints(location[0], location[1], u->getX(), u->getY()) < base_attack_radius /* add is attack cooldown finished condition */) {
            if (attack_cooldown == 0) {
                attack(base_attack_radius, base_attack_sector_angle, base_attackInterval);
                attack_cooldown = base_attackInterval;
            }
        }
        move_AI(u->getX(), u->getY());
    }
}