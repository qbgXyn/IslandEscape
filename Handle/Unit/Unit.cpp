#include "Unit.h"

Unit::Unit(double x, double y) : Handle(x, y) {}


void Unit::gainAttributeFromEffect(Effect &e) {
    Effect::Type type = e.getType();
    switch(type) {
        case Effect::Type::REGEN_INSTANT:
            health += e.getData();
            break;
        case Effect::Type::SPEED:
            max_speed += e.getData();
            break;
        case Effect::Type::INVULNERABLE:
            setInvulnerable();
            break;
        case Effect::Type::INVISIBLE:
            setInvisible();
            break;
    }
}
