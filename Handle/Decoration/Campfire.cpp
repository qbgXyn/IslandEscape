#include "Campfire.h"

const float Campfire::base_collison_radius = 32.0;
const double Campfire::base_max_speed = 0.0;


Campfire::Campfire(Map *map, double x, double y, int inInvulnerable = 1) : Decoration(map, x, y, inInvulnerable) {

}