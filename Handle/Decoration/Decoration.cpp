#include "Decoration.h"


Decoration::Decoration(Map *map, double x, double y, int inInvulnerable) : Handle(map, x, y) {
    category = Handle::Category::DECORATION;
    this->inInvulnerable = inInvulnerable;
}
