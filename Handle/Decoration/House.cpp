#include "House.h"

const float House::base_collison_radius = 32.0;
const double House::base_max_speed = 0.0;


House::House(Map *map, double x, double y, int inInvulnerable) : Decoration(map, x, y, inInvulnerable) {

}
