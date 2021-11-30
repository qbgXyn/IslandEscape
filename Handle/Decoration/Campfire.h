#ifndef CAMPFIRE_H
#define CAMPFIRE_H
/*
//decoration, while it has two function:
//1. re-gain durability of torch
//2. prevent ghost chasing player
*/
#include "Decoration.h"

class Campfire : public Decoration {
    public:
        explicit Campfire(Map *map, double x, double y, int inInvulnerable = 1);
        static const int base_max_health = 10;
        static const int base_collision_radius;
        static const int base_buff_radius;
        static const double base_max_speed;


};
#endif // CAMPFIRE_H
