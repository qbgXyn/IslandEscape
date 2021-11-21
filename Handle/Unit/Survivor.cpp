#include "Survivor.h"
#include <chrono>
const float Survivor::base_collison_radius = 16.0;
const double Survivor::base_max_speed = 20.0;
const float Survivor::base_attackInterval = 1.0;
const float Survivor::base_attack_radius = 16.0;

Survivor::Survivor(Map *map, double x, double y) : Unit(map, x, y) {
    type = Handle::Type::SURVIVOR;
    pathable += Map::Terrain::GRASS;
    pathable += Map::Terrain::STONE;
    pathable += Map::Terrain::SHOAL;
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
    Item::ID id = i->getID();
    int durability = i->getDurability();
    double data = i->getData();

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
        case Item::ID::SPEED_POTION:
            Effect *e = new Effect(Effect::Type::SPEED, data, i->getDuration());
            addEffect(e);
            break;
        case Item::ID::REGEN_INSTANT_POTION:
            Effect *e = new Effect(Effect::Type::REGEN_INSTANT, data, i->getDuration());
            addEffect(e);
            break;
    }

    if (durability > 0) {
        --durability;
        if (durability == 0) {
            delete i;
        }else {
            i->setDurability(durability);
        }
    }
}

bool Survivor::turnOnBoat() const {
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], max_collision_radius); // get all surrounding handle

    vector<Handle*>::const_iterator it_end = list.end(); // check if it collide with existing handle
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) {
        if ((*it)->getType() == Handle::Type::BOAT) {
            // game win!
            return true;
        }
    }
    return false;
}