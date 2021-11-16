#include "Unit.h"
#include "../Inventory/Item_inventory.h"
class Survivor : public Unit {
    public:
        explicit Survivor(double x, double y);
        void attack();
        vector<Item_inventory> Inventory;
};