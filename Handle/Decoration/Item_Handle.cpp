#include "Item_Handle.h"

const int Item_Handle::base_max_health = 1.0;
const float Item_Handle::base_collison_radius = 0.0;
const double Item_Handle::base_max_speed = 0.0;

Item_Handle::Item_Handle(Map *map, double x, double y, int inInvulnerable = 1, int inCollisionless = 1) 
                        :Decoration(map, x, y, inInvulnerable) {
    this->inCollisionless = inCollisionless;

    }