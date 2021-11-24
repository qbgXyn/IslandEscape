#include "Door.h"
#include "../../Map/Map.h"

const float Door::base_collison_radius = 32.0;
const double Door::base_max_speed = 0.0;


Door::Door(Map *map, double x, double y, int inInvulnerable) : Decoration(map, x, y, inInvulnerable) {
    type = Handle::Type::DOOR;
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
}
