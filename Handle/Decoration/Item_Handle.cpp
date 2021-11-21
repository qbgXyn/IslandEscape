#include "Item_Handle.h"

const float Item_Handle::base_collison_radius = 0.0;
const double Item_Handle::base_max_speed = 0.0;

Item_Handle::Item_Handle(Map *map, double x, double y, Item::ID id, int inInvulnerable, int inCollisionless) : Decoration(map, x, y, inInvulnerable) {
    this->inCollisionless = inCollisionless;
    type = Handle::Type::ITEM;
    item = map->createItem(id);
    pathable += Map::Terrain::GRASS;
    pathable += Map::Terrain::STONE;
    pathable += Map::Terrain::SHOAL;

    }

Item* Item_Handle::getCorrespondingItem() const {
    return item;
}