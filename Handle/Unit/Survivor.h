#include "Unit.h"
#include "../Inventory/Item_Inventory.h"

class Survivor : public Unit {
    public:
        const float base_max_health = 10.0;
        const float base_collison_radius = 16.0;

        const float base_damage = 1.0;
        const float base_attackInterval = 1.0;
        const float base_attack_radius = 16.0;
        const float base_armor = 0.0;
        const double base_max_speed = 10;

        explicit Survivor(double x, double y);
        void attack();
        vector<Item_inventory> Inventory;
};
