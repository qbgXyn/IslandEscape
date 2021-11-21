//#include "Handle.h"
#include "../Map/Map.h"
#include "../util.h"
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

Handle::Type Handle::getType() const {
    return type;
}

Handle::Category Handle::getCategory() const {
    return category;
}

bool Handle::isInvulnerable() const {
    return (inInvulnerable > 0);
}

bool Handle::isCollisionless() const {
    return (inCollisionless > 0);
}

bool Handle::isInvisible() const {
    return (inInvisible > 0);
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

bool Handle::hasCollision(const Handle *h) const {
    // if one of them is collisionless
    if (h->isCollisionless() || isCollisionless()) {
        return false;
    }
    double d = map->distanceBetweenPoints(this->location[0], this->location[1], h->location[0], h->location[1]);
    return ( (d - this->collisionRadius - h->collisionRadius) < 0);
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

bool Handle::isCoordinatePathable(double x, double y) const {
    if (!map->isCoordinateInMap(x, y)) {
        return false;
    }

    Map::Terrain terrain = map->getTerrainOfGrid(x, y);
    return pathable(terrain);
}

bool Handle::isCoordinateWalkable(double x, double y) const{
    // check if out of bound or
    // handle can be on that terrain
    if (!isCoordinatePathable(x, y)) {
        return false;
    }

    // no need to check if collisionless
    if(isCollisionless()) {
        return true;
    }

    vector<Handle*> list = map->getHandleGroup(x, y, max_collision_radius); // get all surrounding handle

    vector<Handle*>::const_iterator it_end = list.end(); // check if it collide with existing handle
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) {
        if (hasCollision(*it)) {
            return false;
        }
    }

    return true;

}
