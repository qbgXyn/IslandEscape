#include "Ghost.h"
#include "../../Map/Map.h"

// for simplicity, no collsion means we don't need any algorithm for path finding
const int Ghost::base_collision_radius = 0;

const double Ghost::base_max_speed = 8.0; //base maximum speed
const int Ghost::base_attackInterval = 2*GAME_TICK; //base attack CD
const float Ghost::base_attack_radius = 128.0; //base attack radius
const double Ghost::base_attack_sector_angle = 120.0; //base attack circular angle sector

const double Ghost::patrolRadius = 472.0; //patrol radius of ghost
const double Ghost::detectRadius = 400.0; //detect player radius
const double Ghost::chasingRadius = 900.0; //chasing radius

Ghost::Ghost(Map *map, double x, double y, int species, Handle *chasing_target) : Unit(map, x, y), species(species) { //ghost constructor
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

    max_speed = base_max_speed;
    collisionRadius = base_collision_radius;
    visible_size = base_visible_size;
    health = base_max_health;
    damage = base_damage;
    armor = base_armor; //initalise base value

}

#include <iostream>
void Ghost::update() {

    Handle::update();    
    
    // attack interval section
    if (attackInterval > 0) {
        --attackInterval;
    }

    cout << "update: " << location[0] << " " << location[1] << endl;

    // ai section
    if (state == State::STATIC) {
        while(true) {
            cout << "ghost update - ai - selecting location" << endl;
            randomTargetLocation[0] = map->getRandomDouble(patrolCenterLocation[0] - patrolRadius, patrolCenterLocation[0] + patrolRadius);
            randomTargetLocation[1] = map->getRandomDouble(patrolCenterLocation[1] - patrolRadius, patrolCenterLocation[1] + patrolRadius);
            cout << "ghost update - picking location: " << randomTargetLocation[0] <<  " " << randomTargetLocation[1] << " " << map->distanceBetweenPoints(randomTargetLocation[0], randomTargetLocation[1], patrolCenterLocation[0], patrolCenterLocation[1]) << " " << patrolRadius << endl;
            if (!map->isCoordinateInMap(randomTargetLocation[0], randomTargetLocation[1]))
                continue;
            if (map->distanceBetweenPoints(randomTargetLocation[0], randomTargetLocation[1], patrolCenterLocation[0], patrolCenterLocation[1]) <= patrolRadius) { //randomly walk within the patrol radius
                break;
            }
        }
        state = State::PATROL;
    }else if (state == State::PATROL) {
        cout << "ghost update - ai - patrol" << endl;
        patrol();
    }else if (state == State::CHASE) {
        cout << "ghost update - ai - chase" << endl;
        chase(chasing_target);
    }else if (state == State::RETURN) {
        cout << "ghost update - ai - return" << endl;
        move_AI(patrolCenterLocation[0], patrolCenterLocation[1]);
        double d = std::hypot(location[0] - patrolCenterLocation[0], location[1] - patrolCenterLocation[1]); // distance between itself and patrol center
        cout << d << endl;
        if (map->isDoubleZero(d)) {
            state = State::STATIC;
        }
    }else if (map->isDoubleZero(getVelocity())) {     // if velocity is 0, i.e ghost is static
        cout << "ghost update - ai - reach start point" << endl;
        state = State::STATIC;
    }
}

void Ghost::patrol() {
    double d;
    // if reach the target point
    d = std::hypot(location[0] - randomTargetLocation[0], location[1] - randomTargetLocation[1]);
    cout << "D: " << d << endl;
    if (map->isDoubleZero(d)) {
        state = State::STATIC; // directly go to next random point
        return;
    }

    vector<Handle*> list = map->getHandleGroup(location[0], location[1], detectRadius); // get all surrounding handle within detect radius
    vector<Handle*>::const_iterator it_end = list.end(); 
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) {

        //if within the detect radius has survivor, start chasing
        if ((*it)->getType() == Handle::Type::SURVIVOR && !(*it)->isInvulnerable() && !(*it)->isInvisible()) {
            chasing_target = *it;
            state = State::CHASE;
            return; 
        }
    }

    move_AI(randomTargetLocation[0], randomTargetLocation[1]);

}

#include <iostream>
void Ghost::move_AI(double x, double y) {
    double dx = x - location[0];
    double dy = y - location[1];
    double total = abs(dx+dy);

    // separate max_speed to x and y components by ratio
    velocity[0] = (dx/total) * max_speed;
    velocity[1] = (dy/total) * max_speed;

    cout << "location[0]: " << location[0] << endl;
    cout << "location[1]: " << location[1] << endl;
    cout << "patrolCenterLocation[0]: " << patrolCenterLocation[0] << endl;
    cout << "patrolCenterLocation[1]: " << patrolCenterLocation[1] << endl;
    cout << "randomTargetLocation[0]: " << randomTargetLocation[0] << endl;
    cout << "randomTargetLocation[1]: " << randomTargetLocation[1] << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "dx: " << dx << endl;
    cout << "dy: " << dy << endl;
    cout << "total: " << total << endl;
    cout << "v0: " << velocity[0] << endl;
    cout << "v1: " << velocity[1] << endl;

    //if overshot
    if (abs(velocity[0]) > dx && abs(velocity[1]) > dy) {
        location[0] = x;
        velocity[0] = 0;
        location[1] = y;
        velocity[1] = 0;
        cout << "overshot" << endl;
    }
}

void Ghost::chase(Handle* u) {
    double d = std::hypot(location[0] - patrolCenterLocation[0], location[1] - patrolCenterLocation[1]);

    // condition not fulfilled, return
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
