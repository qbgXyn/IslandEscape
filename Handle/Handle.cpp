//#include "Handle.h"
#include "../Map/Map.h"
Handle::Handle(Map *map, double x, double y) {
    this->map = map;
    location[0] = x;
    location[1] = y;
} 


int Handle::getHealth() const {
    return health;
}

double Handle::getX() const {
    return location[0];
}

double Handle::getY() const {
    return location[1];
}

double Handle::getVelocity() const {
    return hypot(velocity[0], velocity[1]);
}

double Handle::getDirection() const {
    return atan2(velocity[1], velocity[0]) * 180.0 / PI;
}

float Handle::getCollisionRadius() const {
    return collisionRadius;
}

bool Handle::isInvulnerable() const {
    return (inInvulnerable > 0) ? true: false;
}

bool Handle::isCollisionless() const {
    return (inCollisionless > 0) ? true: false;
}

bool Handle::isInvisible() const {
    return (inInvisible > 0) ? true: false;
}

void Handle::setInvulnerable() {
    ++inInvulnerable;
}

void Handle::setInvisible() {
    ++inInvisible;
}

void Handle::setinCollisionless() {
    ++inCollisionless;
}

bool Handle::hasCollision(const Handle &h) {
    if (h.inCollisionless > 0 || inCollisionless > 0) return true; // if one of them is collisionless

    double d = map->distanceBetweenPoints(this->location[0], this->location[1], h.location[0], h.location[1]);
    return (d - this->collisionRadius - h.collisionRadius < 0);
}

void Handle::move() {
    /*
    1. get new position
    2. check collision
    3. if legal, change position, otherwise, set speed to 0

    4. if velocity > 0, and move button released, decrease velocity
    5. if max speed not reached, and move button pressed, increase velocity
    */
}
