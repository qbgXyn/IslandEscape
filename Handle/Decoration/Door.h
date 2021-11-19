#ifndef DOOR_H
#define DOOR_H

#include "Decoration.h"

class Door : public Decoration {
    private:
        static const int base_max_health = 10;
        static const float base_collison_radius;
        static const double base_max_speed;
    public:
        explicit Door(Map *map, double x, double y, int inInvulnerable = 1);

        Decoration::Type get_type() const {return Decoration::Type::DOOR;}

};
#endif // DOOR_H
