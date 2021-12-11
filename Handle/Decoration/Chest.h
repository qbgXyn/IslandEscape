#ifndef CHEST_H
#define CHEST_H
/*
//chest is used to contain items, while survivor break the chest, it drops out all items stored inside
*/
#include "Decoration.h"
#include "../../Item/Item.h"

class Chest : public Decoration {
    private:       
        // for simplicity, fix the size
        static const int maxSlotOfInventory = 9;
        Item::ID Inventory[maxSlotOfInventory];
    public:
        explicit Chest(Map *map, double x, double y, int inInvulnerable = 0);
        static const int base_max_health = 1;
        static const int base_collision_radius;
        static const double base_max_speed;
        virtual ~Chest();
        virtual void ChestAddItem(Item::ID id) override;


};
#endif // CHEST_H
