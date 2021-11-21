#include "Unit.h"

Unit::Unit(Map *map, double x, double y) : Handle(map, x, y) {
    type = Handle::Type::UNIT;
}


void Unit::gainAttributeFromEffect(Effect *e) {
    Effect::Type type = e->getType();
    switch(type) {
        case Effect::Type::REGEN_INSTANT:
            health += e->getData();
            break;
        case Effect::Type::SPEED:
            max_speed += e->getData();
            break;
        case Effect::Type::INVULNERABLE:
            setInvulnerable();
            break;
        case Effect::Type::INVISIBLE:
            setInvisible();
            break;
    }
}

void Unit::addEffect(Effect *e) {
    gainAttributeFromEffect(e);
    EffectList.push_back(e);
}

