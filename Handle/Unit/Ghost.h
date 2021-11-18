#include "Unit.h"

class Ghost : public Unit {
    private:
        Unit *chasing_target;
    public:
        const float base_max_health = 5.0;
        const float base_collison_radius = 0.0;
// for simplicity, no collsion means we don't need any algorithm for path finding
        const float base_damage = 1.0;
        const float base_attackInterval = 1.0;
        const float base_attack_radius = 16.0;
        const float base_armor = 1.0;

        explicit Ghost(Map *map, double x, double y, Unit *chasing_target);
        void attack();
        void patrol();

};
