#include "Ghost.h"

Ghost::Ghost(Map *map, double x, double y, Unit *chasing_target = nullptr) : Unit(map, x, y) {
    this->chasing_target = chasing_target;
}


void Ghost::attack() {

}


void Ghost::patrol() {

}
