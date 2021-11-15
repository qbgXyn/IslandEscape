#include "Ghost.h"

const float Ghost::base_max_health = 5.0;
const float Ghost::base_collison_radius = 0.0; // for simplicity, no collsion means we don't need any algorithm for path finding

const float Ghost::base_damage = 1.0;
const float Ghost::base_attackInterval = 1.0;
const float Ghost::base_attack_radius = 16.0;
const float Ghost::base_armor = 1.0;


Ghost::Ghost(double x, double y) : Unit(x, y) {}


void Ghost::attack() {

}


void Ghost::patrol() {

}