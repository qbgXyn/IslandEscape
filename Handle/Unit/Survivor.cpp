#include "Survivor.h"
#include "../Decoration/Item_Handle.h"
#include "../../Map/Map.h"
#include <chrono>

//#include <bits/stdc++.h>
const float Survivor::base_collison_radius = 16.0; 
const double Survivor::base_max_speed = 20.0; 
const float Survivor::base_attackInterval = 1.0; 
const float Survivor::base_attack_radius = 16.0; 
const double Survivor::base_attack_sector_angle = 60.0; // set base index for survivor

Survivor::Survivor(Map *map, double x, double y) : Unit(map, x, y) { //constructor
    type = Handle::Type::SURVIVOR;
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    pathable += Terrain::Type::SHOAL; //player can walk through grass, stone and shoal ground but not ocean

    visible_size = base_visible_size;
    health = base_max_health;
    damage = base_damage;
    armor = base_armor; //initalize value

    Inventory[0] = new Item_inventory {Item::ID::SWORD}; //by default give a sword to the player at the beginning in the first left item bar and hold it
    Inventory[1] = new Item_inventory {Item::ID::TORCH}; //by deafult give a torch to the player 
}


bool Survivor::isInventoryFull() const { //check if the "bag" is full
    int counter = 0;
    for (int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != nullptr) {
            ++counter;
        }
    }
    return counter >= maxSlotOfInventory;
}

void Survivor::useItem(Item_inventory *i) { //use the holding item
    if (i == nullptr) return; //check if holding an item
    Item *item = i->item;
    Item::ID id = item->getID();
    int durability = item->getDurability();
    double data = item->getData();
    double duration = item->getDuration(); //get the private data of item
    switch(id) {
        case Item::ID::KEY:
            turnOnBoat();
            return; // no need to reduce durability
        case Item::ID::TORCH:
        case Item::ID::TORCH_LIT:
            switchTorchState();
            return; // no need to reduce durability
        case Item::ID::ROCK:
            // further information needed for implementation
            break;
        case Item::ID::BELL:
            // further information needed for implementation
            break;
        case Item::ID::SPEED_POTION: {
            Effect *e = new Effect(Effect::Type::SPEED, data, duration);
            addEffect(e);
            break;
        }
        case Item::ID::REGEN_INSTANT_POTION: {
            Effect *e = new Effect(Effect::Type::REGEN_INSTANT, data, duration);
            addEffect(e);
            break;
        }
        case Item::ID::SWORD:
            setDamage(item->getData());
            attack(base_attack_radius, base_attack_sector_angle, base_attackInterval);
            break;
    }

    if (durability > 0) {
        --durability;
        if (durability == 0) {
            delete i;
        }else {
            item->setDurability(durability);
        }
    }
}


void Survivor::pickupItem() { //[pick up a item nearby on the ground]
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], collisionRadius); // get all surrounding handles

    Handle* h;

    vector<Handle*>::const_iterator it_end = list.end(); // check if it collide with existing handle
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) { // iterate all handle
        h = *it;
        if (h->getType() == Handle::Type::ITEM && !isInventoryFull()) { // if it's item
            for(int index = 0; index < maxSlotOfInventory; ++index) { // iterate all slot in inventory
                if (Inventory[index] == nullptr) {                  // find a empty slot of inventory
                    Inventory[index] = new Item_inventory {*(h->getCorrespondingItem())};
                    break;
                }
            }
        }
    }
}


void Survivor::dropItem(Item_inventory *i) {
    if (i != nullptr) { //check if holding an item
        map->createItem_Handle(i->item->getID(), location[0], location[1]);
        // Item_Handle* ih = new Item_Handle{map, this->location[0], this->location[1], i->item->getID()};
        // map->List.push_back(ih);
        delete i; //when drop the item, remove it from the array but will not move other item positon in the array
    }
}

void Survivor::switchTorchState() { //switch between torch and set a new durability
    if (Inventory[selectedItemIndex] == nullptr) return; //chack if not holding any item 

    int durability;
    Item::ID id = Inventory[selectedItemIndex]->item->getID();

    if (id == Item::ID::TORCH || id == Item::ID::TORCH_LIT) {
        durability = Inventory[selectedItemIndex]->item->getDurability();
        delete Inventory[selectedItemIndex]; //used the torch to set the new durability

        if (id == Item::ID::TORCH && durability > 0) {
            Inventory[selectedItemIndex] = new Item_inventory {Item::ID::TORCH_LIT};
            setVisibleSize(getVisibleSize() + Inventory[selectedItemIndex]->item->getData()); //set durability if using torch_lit
        }
        else {
            Inventory[selectedItemIndex] = new Item_inventory {Item::ID::TORCH};
            setVisibleSize(getVisibleSize() - Inventory[selectedItemIndex]->item->getData()); // set durability if using torch
        }
        Inventory[selectedItemIndex]->item->setDurability(durability);
    }

    // if (Inventory[selectedItemIndex]->item->getID() == Item::ID::TORCH) {
    //     durability = Inventory[selectedItemIndex]->item->getDurability();
    //     delete Inventory[selectedItemIndex];

    //     Inventory[selectedItemIndex] = new Item_inventory {Item::ID::TORCH_LIT};
    //     Inventory[selectedItemIndex]->item->setDurability(durability);

    // }else if (Inventory[selectedItemIndex]->item->getID() == Item::ID::TORCH_LIT) {
    //     durability = Inventory[selectedItemIndex]->item->getDurability();
    //     delete Inventory[selectedItemIndex];

    //     Inventory[selectedItemIndex] = new Item_inventory {Item::ID::TORCH};
    //     Inventory[selectedItemIndex]->item->setDurability(durability);
    // }
}


int Survivor::getTorchTime() const{ //return the torch durability
    Item::ID id;
    for (int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != nullptr) { //check if holding a item
            id = Inventory[i]->item->getID();
            if (id == Item::ID::TORCH || id == Item::ID::TORCH_LIT) {
                return Inventory[i]->item->getDurability();
            }
        }

    }
    return 0;
}

void Survivor::setTorchTime(int time) { //set up the torch durability
    Item::ID id; 
    for (int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != nullptr) {
            id = Inventory[i]->item->getID();
            if (id == Item::ID::TORCH || id == Item::ID::TORCH_LIT) {
                Inventory[i]->item->setDurability(time);
                return;
            }
        }

    }
}

bool Survivor::turnOnBoat() const { //if can turnon the boat, end the game
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], collisionRadius); // get all surrounding handle

    vector<Handle*>::const_iterator it_end = list.end(); // check if it collide with existing handle
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) {
        if ((*it)->getType() == Handle::Type::BOAT) {
            // game win!
            return true;
        }
    }
    return false;
}

bool Survivor::hasItem(Item::ID id) const { //loop through the item array to check the item
    for (int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != nullptr && Inventory[i]->item->getID() == id) { //search item name
            return true;
        }
    }
    return false;
}

void Survivor::Switch_selectedItem_Index(int index) //change the index item so that it refer to different item in the item array
{
    selectedItemIndex = index;
}