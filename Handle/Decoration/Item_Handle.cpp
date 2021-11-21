#include "Item_Handle.h"

const float Item_Handle::base_collison_radius = 0.0;
const double Item_Handle::base_max_speed = 0.0;

Item_Handle::Item_Handle(Map *map, Category category, Type type, double x, double y, int inInvulnerable, int inCollisionless) 
                        :Decoration(map, category, type, x, y, inInvulnerable) {
    this->inCollisionless = inCollisionless;
    pathable += Map::Terrain::GRASS;
    pathable += Map::Terrain::STONE;
    pathable += Map::Terrain::SHOAL;

    }