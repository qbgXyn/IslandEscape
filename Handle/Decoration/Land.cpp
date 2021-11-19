#include "Land.h"

const float Land::base_collison_radius = 32.0;
const double Land::base_max_speed = 0.0;


Land::Land(Map *map, int x, int y, int inInvulnerable) : Decoration(map, x, y, inInvulnerable) {

}