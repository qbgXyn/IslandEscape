#include "Campfire.h"

const float Campfire::base_collison_radius = 32.0;
const double Campfire::base_max_speed = 0.0;


Campfire::Campfire(Map *map, Category category, Type type, double x, double y, int inInvulnerable) : Decoration(map, category, type, x, y, inInvulnerable) {
    pathable += Map::Terrain::GRASS;
    pathable += Map::Terrain::STONE;
}
