#include "Ghost.h"
#include "../../Map/Map.h"

// for simplicity, no collsion means we don't need any algorithm for path finding
const float Ghost::base_collision_radius = 0.0;

const double Ghost::base_max_speed = 20.0; //base maximum speed
const int Ghost::base_attackInterval = 3*GAME_TICK; //base attack CD
const float Ghost::base_attack_radius = 32.0; //base attack radius
const double Ghost::base_attack_sector_angle = 60.0; //base attack circular angle sector

const double Ghost::patrolRadius = 256.0; //patrol radius of ghost 
const double Ghost::detectRadius = 400.0; //detect player radius
const double Ghost::chasingRadius = 800.0; //chasing radius


Ghost::Ghost(Map *map, double x, double y, Handle *chasing_target) : Unit(map, x, y) { //ghost constructor
    type = Handle::Type::GHOST;
    this->chasing_target = chasing_target;
    patrolCenterLocation[0] = x;
    patrolCenterLocation[1] = y;
    state = State::STATIC;
    //ghost can walk on all area of the map, include the ocean which player cannot
    // so in this way we don't need any algorithm for path finding
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    pathable += Terrain::Type::SHOAL;
    pathable += Terrain::Type::OCEAN;
    pathable += Terrain::Type::VOID; 


    visible_size = base_visible_size;
    health = base_max_health;
    damage = base_damage;
    armor = base_armor; //initalise base value
}

void Ghost::update() {

    Handle::update();    
    
    // attack interval section
    if (attackInterval > 0) {
        --attackInterval;
    }

    // ai section
    if (state == State::STATIC) {
        while(true) {
            randomTargetLocation[0] = map->getRandomDouble(location[0] - patrolRadius, location[0] + patrolRadius);
            randomTargetLocation[1] = map->getRandomDouble(location[1] - patrolRadius, location[1] + patrolRadius);
            if (std::hypot(randomTargetLocation[0], randomTargetLocation[1]) <= patrolRadius) { //randomly walk within the patrol radius
                break;
            }
        }
        state = State::PATROL;
    }else if (state == State::PATROL) {
        patrol();
    }else if (state == State::CHASE) {
        chase(chasing_target);
    }else if (state == State::RETURN) {
        move_AI(patrolCenterLocation[0], patrolCenterLocation[1]);
    }else if (velocity[0] <= ECLIPSE && velocity[0] >= -ECLIPSE && velocity[1] <= ECLIPSE && velocity[1] >= -ECLIPSE) {     // if velocity is 0, i.e ghost is static
        state = State::STATIC;
    }
}

void Ghost::patrol() {
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], detectRadius); // get all surrounding handle within attack radius

    vector<Handle*>::const_iterator it_end = list.end(); 
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) {
        if ((*it)->getType() == Handle::Type::SURVIVOR && !(*it)->isInvulnerable() && !(*it)->isInvisible()) {
            chasing_target = *it;
            state = State::CHASE;
            return; //if within the detect radius has survivor, start chasing
        }
    }

    move_AI(randomTargetLocation[0], randomTargetLocation[1]);

}


void Ghost::move_AI(double x, double y) {
    double dx = abs(x - location[0]);
    double dy = abs(y - location[1]);
    double total = dx+dy;

    // separate max_speed to x and y components by ratio
    velocity[0] = dx/total * max_speed;
    velocity[1] = dy/total * max_speed;
}

void Ghost::chase(Handle* u) {
    double d = std::hypot(location[0] - patrolCenterLocation[0], location[1] - location[0]);
    if (d > chasingRadius || !isHandleVisible(u) || u->isInvulnerable() || u->isInvisible()) {
        move_AI(patrolCenterLocation[0], patrolCenterLocation[1]);
        chasing_target = nullptr;
        state = State::RETURN;
    }else {
        if (map->distanceBetweenPoints(location[0], location[1], u->getX(), u->getY()) < base_attack_radius /* add is attack cooldown finished condition */) {
            if (attackInterval == 0) {
                attack(base_attack_radius, base_attack_sector_angle);
                attackInterval = base_attackInterval;
            }
        }
        move_AI(u->getX(), u->getY());
    }
}
