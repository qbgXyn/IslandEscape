#include "Decoration.h"


Decoration::Decoration(double x, double y, int inInvulnerable = 1) : Handle(x, y) {
    this->inInvulnerable = inInvulnerable;
}
