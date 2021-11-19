#include "../Handle.h"
class Decoration : public Handle {
    public:
        enum class Type {
            LAND = 1,
            HOUSE = 2,
            DOOR = 3,
            TREE = 4,
            CAMPFIRE = 5,
            BOAT = 6
        };

        Decoration(Map *map, double x, double y, int inInvulnerable = 1);

        virtual Decoration::Type get_type() const = 0;

};
