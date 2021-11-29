#include "Boat.h"

const float Boat::base_collision_radius = 32.0;
const double Boat::base_max_speed = 0.0;


Boat::Boat(Map *map, double x, double y, int inInvulnerable) : Decoration(map, x, y, inInvulnerable) {
    type = Handle::Type::BOAT;
    pathable += Terrain::Type::SHOAL;
    pathable += Terrain::Type::OCEAN;
}
