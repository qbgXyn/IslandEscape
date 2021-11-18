#include "Tree.h"

const float Tree::base_collison_radius = 32.0;
const double Tree::base_max_speed = 0.0;


Tree::Tree(Map *map, double x, double y, int inInvulnerable = 1) : Decoration(map, x, y, inInvulnerable) {

}