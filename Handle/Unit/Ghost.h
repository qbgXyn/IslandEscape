#include "Unit.h"

class Ghost : public Unit {
    private:
        Unit *chasing_target;
    public:
        static const int base_max_health = 5;
        static const float base_collison_radius;
        static const double base_max_speed;

        static const int base_damage = 1;
        static const float base_attackInterval;
        static const float base_attack_radius;
        static const int base_armor = 1;

        explicit Ghost(Map *map, double x, double y, Unit *chasing_target);
        void attack();
        void patrol();

};
