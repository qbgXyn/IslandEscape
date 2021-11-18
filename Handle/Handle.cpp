#include "Handle.h"
#include "../Map.h"
explicit Handle::Handle(Map *map, double x, double y) {
    this->map = map;
    location[0] = x;
    location[1] = y;
} 

const float Handle::base_max_health = 1.0;

bool Handle::hasCollision(const Handle &h) {
    if (h.inCollisionless > 0 || inCollisionless > 0) return true; // if one of them is collisionless

    double d = map->distanceBetweenPoints(this->location[0], this->location[1], h.location[0], h.location[1]);
    return (d - this->collisionRadius - h.collisionRadius < 0);
}

void Handle::move() {
    
}