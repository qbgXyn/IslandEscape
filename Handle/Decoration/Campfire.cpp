#include "Campfire.h"

const int Campfire::base_collision_radius = 32.0;
const int Campfire::base_buff_radius = 128;
const double Campfire::base_max_speed = 0.0;


Campfire::Campfire(Map *map, double x, double y, int inInvulnerable) : Decoration(map, x, y, inInvulnerable) {
    type = Handle::Type::CAMPFIRE;
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    collisionRadius = base_collision_radius;
}
