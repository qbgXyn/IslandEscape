#include "Decoration.h"

class Campfire : public Decoration {
    private:
        static const int base_max_health = 10;
        static const float base_collison_radius;
        static const double base_max_speed;
    public:
        explicit Campfire(Map *map, double x, double y, int inInvulnerable);

};