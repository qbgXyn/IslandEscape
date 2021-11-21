#include "Ghost.h"

const float Ghost::base_collison_radius = 0.0;
// for simplicity, no collsion means we don't need any algorithm for path finding
const double Ghost::base_max_speed = 20.0;
const float Ghost::base_attackInterval = 3.0;
const float Ghost::base_attack_radius = 16.0;


Ghost::Ghost(Map *map, double x, double y, Unit *chasing_target) : Unit(map, x, y) {
    type = Handle::Type::GHOST;
    this->chasing_target = chasing_target;
    pathable += Map::Terrain::GRASS;
    pathable += Map::Terrain::STONE;
    pathable += Map::Terrain::SHOAL;
    pathable += Map::Terrain::OCEAN;
    pathable += Map::Terrain::VOID;
}

void Ghost::attack() {

}


void Ghost::patrol() {

}
