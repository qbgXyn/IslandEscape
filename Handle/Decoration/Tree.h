#include "Decoration.h"

class Tree : public Decoration {
    private:
        static const int base_max_health;
        static const float base_collison_radius;
        static const double base_max_speed;
    public:
        explicit Tree(Map *map, double x, double y, int inInvulnerable);

};