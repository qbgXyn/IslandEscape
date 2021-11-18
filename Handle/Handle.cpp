//#include "Handle.h"
#include "../Map.h"
Handle::Handle(Map *map, double x, double y) {
    this->map = map;
    location[0] = x;
    location[1] = y;
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
