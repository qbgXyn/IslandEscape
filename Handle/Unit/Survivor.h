#ifndef SURVIVOR_H
#define SURVIVOR_H

#include "Unit.h"
#include "../Inventory/Item_Inventory.h"

class Survivor : public Unit { //survivor is the derived class of unit
    public:
        explicit Survivor(Map *map, double x, double y); //player constructor
        static const int base_max_health = 10; //base maximum health of player
        static const float base_collison_radius; //base collision radius of player
        static const double base_max_speed; //base maximum movement speed 
        
        static const int base_damage = 0; //base melee damage
        static const float base_attackInterval; //base melee CD
        static const float base_attack_radius; //base melee radius
        static const double base_attack_sector_angle; //base melee sector angle
        static const int base_armor = 0; //basic armor
        static const int base_visible_size = 3; //basic visibility of player

        static const int maxSlotOfInventory = 9; //the maximum amount of item player can store, like the bag capacbility
        int selectedItemIndex = 0; //by default the player will have the item on the first left box in the buttom item bar 

        // void attack();
        Item_inventory* Inventory[maxSlotOfInventory] = {}; //a array of item which acts like a bag for the player to store the items

        bool isInventoryFull() const; //check if the inventory is full
        void useItem(Item_inventory *i); //use the currently selected item
        void pickupItem(); //pick up item on ground
        void dropItem(Item_inventory *i); //drop the item on ground 

        void switchTorchState();  //switch between torch and set a new durability
        int getTorchTime() const; //return the torch time
        void setTorchTime(int time);  //set up the torch durability

        bool hasItem(Item::ID id) const; //check if player has the item

        void Switch_selectedItem_Index(int index); //change the index item so that it refer to different item in the item array, so that when press 1-9 key, change the color of the item bar background to show the selection

        bool turnOnBoat() const; //start the boat and end the game
};
#endif // SURVIVOR_H
