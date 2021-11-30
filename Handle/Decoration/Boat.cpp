#include "Boat.h"

const int Boat::base_collision_radius = 32;
const double Boat::base_max_speed = 0.0;
const int Boat::base_turnOn_radius = 96;


Boat::Boat(Map *map, double x, double y, int inInvulnerable) : Decoration(map, x, y, inInvulnerable) {
    type = Handle::Type::BOAT;
    pathable += Terrain::Type::SHOAL;
    pathable += Terrain::Type::OCEAN;
    collisionRadius = base_collision_radius;
}
