#include "Unit.h"

Unit::Unit(Map *map, double x, double y) : Handle(map, x, y) {
    category = Handle::Category::UNIT;
}


float Unit::getDamage() const {
    return damage;
}
float Unit::getArmor() const {
    return armor;
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

bool Unit::insideSector(const Handle *h, double sector_angle) const
{
    double half_angle = sector_angle / 2;
    double current_direction = this -> getDirection();
    double start_angle = current_direction - half_angle;
    double end_angle = current_direction + half_angle;
    double target_handle_angle = atan(h -> location[1] / h -> location[0]);
    if (target_handle_angle >= start_angle && target_handle_angle <= end_angle)
    {
        return true;
    }
    return false;
}