#ifndef CHEST_H
#define CHEST_H

#include "Decoration.h"\
#include "../../Item/Item.h"

class Chest : public Decoration {
    private:
        static const int base_max_health = 1;
        static const float base_collison_radius;
        static const double base_max_speed;
        
        // for simplicity, fix the size
        static const int maxSlotOfInventory = 9;
        Item::ID Inventory[maxSlotOfInventory];
    public:
        explicit Chest(Map *map, double x, double y, int inInvulnerable = 0);
        virtual ~Chest();
        virtual void ChestAddItem(Item::ID id);


};
#endif // CHEST_H
