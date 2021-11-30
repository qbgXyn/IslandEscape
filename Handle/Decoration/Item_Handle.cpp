#include "Item_Handle.h"
#include "../../Map/Map.h"

const float Item_Handle::base_collision_radius = 0.0;
const double Item_Handle::base_max_speed = 0.0;

Item_Handle::Item_Handle(Map *map, double x, double y, Item::ID id, int inInvulnerable, int inCollisionless) : Decoration(map, x, y, inInvulnerable) {
    this->inCollisionless = inCollisionless;
    type = Handle::Type::ITEM;
    item = map->createItem(id);
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    pathable += Terrain::Type::SHOAL;

}

Item_Handle::Item_Handle(Map *map, double x, double y, Item *item, int inInvulnerable, int inCollisionless) : Decoration(map, x, y, inInvulnerable) {
    this->inCollisionless = inCollisionless;
    type = Handle::Type::ITEM;
    this->item = map->copyItem(item);
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    pathable += Terrain::Type::SHOAL;

}

Item_Handle::~Item_Handle() {
    delete item;
}


Item* Item_Handle::getCorrespondingItem() const {
    return item;
}
