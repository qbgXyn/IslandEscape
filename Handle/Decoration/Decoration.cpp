#include "Decoration.h"


Decoration::Decoration(Map *map, double x, double y, int inInvulnerable = 1) : Handle(map, x, y) {
    this->inInvulnerable = inInvulnerable;
}
