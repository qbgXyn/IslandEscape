#include "Survivor.h"
#include "../Decoration/Item_Handle.h"
#include "../../Map/Map.h"
#include <chrono>

//#include <bits/stdc++.h>
const float Survivor::base_collison_radius = 16.0; 
const double Survivor::base_max_speed = 20.0;
const float Survivor::base_attackInterval = 1.0;
const float Survivor::base_attack_radius = 16.0;
const double Survivor::base_attack_sector_angle = 60.0;

Survivor::Survivor(Map *map, double x, double y) : Unit(map, x, y) {
    type = Handle::Type::SURVIVOR;
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    pathable += Terrain::Type::SHOAL;

    visible_size = base_visible_size;
    health = base_max_health;
    damage = base_damage;
    armor = base_armor;

    Inventory[0] = new Item_inventory {Item::ID::SWORD};
    Inventory[1] = new Item_inventory {Item::ID::TORCH};
}

// void Survivor::attack() {
//     //set attack interval of survivor

//      auto t_start = std::chrono::high_resolution_clock::now();
//     /*get all Handle that within radius (60 degree of the circle(radius = attack_radius, center = Coordinate(Survivor)) in front of Survivor)
//     if :
//         1. Handle is not invulnerable
//         2. Handle is Unit
//         3. attack(Survivor) > armor(Unit)
//     then
//     deal (attack(Survivor) - armor(Unit)) amount of attack to Unit
//     */
//     vector<Handle*> list = map->getHandleGroup(location[0], location[1], base_attack_radius); // get all surrounding handle within attack radius

//     vector<Handle*>::const_iterator it_end = list.end(); 
//     for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) 
//     {
//         if (isInsideSector(*it, base_attack_sector_angle) == true) // check if it within attack sector range
//         {
//             if (!isInvulnerable()) //check if it is vulnerable
//             {
//                 if ((*it) -> getCategory() == Handle::Category::UNIT) // check if it is Unit
//                 {
//                     if (this -> getDamage() >= (*it) -> getArmor()) // check if attack > armor
//                     {
//                         int newHealth = this -> getHealth() - (this -> getDamage() - (*it) -> getArmor());
//                         this -> setHealth(newHealth);
//                     }
//                 }
//             }
//         }

//     }
//     while (true)
//     {
//     auto t_end = std::chrono::high_resolution_clock::now();
//     if (std::chrono::duration<float, milli>(t_end - t_start).count() > 1 / base_attackInterval)
//     {
//         //cout << chrono::duration<float, milli>(t_end - t_start).count() << endl;
//         break;
//     }
//     }
// }

bool Survivor::isInventoryFull() const {
    int counter = 0;
    for (int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != nullptr) {
            ++counter;
        }
    }
    return counter >= maxSlotOfInventory;
}

void Survivor::useItem(Item_inventory *i) {
    if (i == nullptr) return;
    Item *item = i->item;
    Item::ID id = item->getID();
    int durability = item->getDurability();
    double data = item->getData();
    double duration = item->getDuration();
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


void Survivor::pickupItem() {
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], collisionRadius); // get all surrounding handle

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
    if (i != nullptr) {
        map->createItem_Handle(i->item->getID(), location[0], location[1]);
        // Item_Handle* ih = new Item_Handle{map, this->location[0], this->location[1], i->item->getID()};
        // map->List.push_back(ih);
        delete i;
    }
}

void Survivor::switchTorchState() { //switch between torch and set a new durability
    if (Inventory[selectedItemIndex] == nullptr) return;

    int durability;
    Item::ID id = Inventory[selectedItemIndex]->item->getID();

    if (id == Item::ID::TORCH || id == Item::ID::TORCH_LIT) {
        durability = Inventory[selectedItemIndex]->item->getDurability();
        delete Inventory[selectedItemIndex];

        if (id == Item::ID::TORCH && durability > 0) {
            Inventory[selectedItemIndex] = new Item_inventory {Item::ID::TORCH_LIT};
            setVisibleSize(getVisibleSize() + Inventory[selectedItemIndex]->item->getData());
        }else {
            Inventory[selectedItemIndex] = new Item_inventory {Item::ID::TORCH};
            setVisibleSize(getVisibleSize() - Inventory[selectedItemIndex]->item->getData());
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
        if (Inventory[i] != nullptr) {
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
        if (Inventory[i] != nullptr && Inventory[i]->item->getID() == id) {
            return true;
        }
    }
    return false;
}

void Survivor::Switch_selectedItem_Index(int index) //change the index item so that it refer to different item in the item array
{
    selectedItemIndex = index;
}