#include "Decoration.h"


Decoration::Decoration(Map *map, Category category, Type type, double x, double y, int inInvulnerable) : Handle(map, category, type, x, y) {
    this->inInvulnerable = inInvulnerable;
}
