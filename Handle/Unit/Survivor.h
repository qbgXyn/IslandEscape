#ifndef SURVIVOR_H
#define SURVIVOR_H

#include "Unit.h"
#include "../Inventory/Item_Inventory.h"

class Survivor : public Unit {
    public:
        explicit Survivor(Map *map, double x, double y);
        static const int base_max_health = 10;
        static const float base_collison_radius;
        static const double base_max_speed;
        
        static const int base_damage = 0;
        static const float base_attackInterval;
        static const float base_attack_radius;
        static const double base_attack_sector_angle;
        static const int base_armor = 0;
        static const int base_visible_size = 3;

        static const int maxSlotOfInventory = 9;
        int selectedItemIndex;

        // void attack();
        Item_inventory* Inventory[maxSlotOfInventory] = {};

        bool isInventoryFull() const;
        void useItem(Item_inventory *i);
        void pickupItem();
        void dropItem(Item_inventory *i);

        void switchTorchState();
        int getTorchTime() const;
        void setTorchTime(int time);

        bool hasItem(Item::ID id) const;


        bool turnOnBoat() const;
};
#endif // SURVIVOR_H
