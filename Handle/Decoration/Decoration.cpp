#include "Decoration.h"


Decoration::Decoration(Map *map, double x, double y, int inInvulnerable) : Handle(map, x, y) {
    type = Handle::Type::DECORATION;
    this->inInvulnerable = inInvulnerable;
}
