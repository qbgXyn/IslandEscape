#include "House.h"

const float House::base_collison_radius = 32.0;
const double House::base_max_speed = 0.0;


House::House(Map *map, Category category, Type type, double x, double y, int inInvulnerable) : Decoration(map, category, type, x, y, inInvulnerable) {
    pathable += Map::Terrain::GRASS;
    pathable += Map::Terrain::STONE;
}
