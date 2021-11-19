#ifndef DECORATION_H
#define DECORATION_H

#include "../Handle.h"
class Decoration : public Handle {
    public:
        enum class Type {
            HOUSE = 1,
            DOOR = 2,
            TREE = 3,
            CAMPFIRE = 4,
            BOAT = 5
        };

        Decoration(Map *map, double x, double y, int inInvulnerable = 1);

        virtual Decoration::Type get_type() const = 0;

};
#endif // DECORATION_H
