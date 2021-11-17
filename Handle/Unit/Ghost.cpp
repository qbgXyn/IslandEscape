#include "Ghost.h"

Ghost::Ghost(double x, double y, Unit *chasing_target = nullptr) : Unit(x, y) {
    this->chasing_target = chasing_target;
}


void Ghost::attack() {

}


void Ghost::patrol() {

}
