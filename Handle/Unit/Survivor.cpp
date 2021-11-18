#include "Survivor.h"

const float Survivor::base_collison_radius = 16.0;
const double Survivor::base_max_speed = 20.0;
const float Survivor::base_attackInterval = 1.0;
const float Survivor::base_attack_radius = 16.0;

Survivor::Survivor(Map* map, double x, double y) : Unit(map, x, y) {
}

void Survivor::attack() {
    
}