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
}

void Survivor::attack() {
    //set attack interval of survivor

     auto t_start = std::chrono::high_resolution_clock::now();
    /*get all Handle that within radius (60 degree of the circle(radius = attack_radius, center = Coordinate(Survivor)) in front of Survivor)
    if :
        1. Handle is not invulnerable
        2. Handle is Unit
        3. attack(Survivor) > armor(Unit)
    then
    deal (attack(Survivor) - armor(Unit)) amount of attack to Unit
    */
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], base_attack_radius); // get all surrounding handle within attack radius

    vector<Handle*>::const_iterator it_end = list.end(); 
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) 
    {
        if (isInsideSector(*it, base_attack_sector_angle) == true) // check if it within attack sector range
        {
            if (!isInvulnerable()) //check if it is vulnerable
            {
                if ((*it) -> getCategory() == Handle::Category::UNIT) // check if it is Unit
                {
                    if (this -> getDamage() >= (*it) -> getArmor()) // check if attack > armor
                    {
                        int newHealth = this -> getHealth() - (this -> getDamage() - (*it) -> getArmor());
                        this -> setHealth(newHealth);
                    }
                }
            }
        }

    }
    while (true)
    {
    auto t_end = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<float, milli>(t_end - t_start).count() > 1 / base_attackInterval)
    {
        //cout << chrono::duration<float, milli>(t_end - t_start).count() << endl;
        break;
    }
    }
}

bool Survivor::isInventoryFull() const {
    return (Inventory.size() == maxSlotOfInventory);
}

void Survivor::useItem(Item_inventory *i) {
    Item *item = i->item;
    Item::ID id = item->getID();
    int durability = item->getDurability();
    double data = item->getData();
    double duration = item->getDuration();
    switch(id) {
        case Item::ID::KEY:
            turnOnBoat();
            break;
        case Item::ID::TORCH:
            // further information needed for implementation
            break;
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

    Item_inventory* i;
    Handle* h;

    vector<Handle*>::const_iterator it_end = list.end(); // check if it collide with existing handle
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) {
        h = *it;
        if (h->getType() == Handle::Type::ITEM && !isInventoryFull()) {
            i = new Item_inventory {*(h->getCorrespondingItem())};
            Inventory.push_back(i);
            delete h;
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


bool Survivor::turnOnBoat() const {
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
