#include "Door.h"

const float Door::base_collison_radius = 32.0;
const double Door::base_max_speed = 0.0;


Door::Door(Map *map, int x, int y, int inInvulnerable) : Decoration(map, x, y, inInvulnerable) {

}