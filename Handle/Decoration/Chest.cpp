#include "Chest.h"
#include "../../Map/Map.h"

const float Chest::base_collision_radius = 32.0;
const double Chest::base_max_speed = 0.0;


Chest::Chest(Map *map, double x, double y, int inInvulnerable) : Decoration(map, x, y, inInvulnerable) {
    type = Handle::Type::CHEST;
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    collisionRadius = base_collision_radius;
    for(int i = 0; i < maxSlotOfInventory; ++i) {
        Inventory[i] = Item::ID::EMPTY;
    }
}


Chest::~Chest() {
    for(int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != Item::ID::EMPTY) {
            this->map->createItem_Handle(Inventory[i], location[0], location[1]);
        }
    }
}

void Chest::ChestAddItem(Item::ID id) {
    for(int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] == Item::ID::EMPTY) {
            Inventory[i] = id;
            return;
        }
    }
}
