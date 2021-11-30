#include "Tree.h"

const int Tree::base_collision_radius = 32;
const double Tree::base_max_speed = 0.0;


Tree::Tree(Map *map, double x, double y, int species, int inInvulnerable) : Decoration(map, x, y, inInvulnerable), species(species) {
    type = Handle::Type::TREE;
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    collisionRadius = base_collision_radius;
}
