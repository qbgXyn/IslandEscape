#ifndef BOAT_H
#define BOAT_H
/*
//when survivor turns on the boat(using a key searched on the island), game wins
*/
#include "Decoration.h"

class Boat : public Decoration {
    public:
        explicit Boat(Map *map, double x, double y, int inInvulnerable = 1);
        static const int base_max_health = 10;
        static const int base_collision_radius;
        static const int base_turnOn_radius;
        static const double base_max_speed;


};
#endif // BOAT_H
