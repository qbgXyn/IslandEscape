#include "Unit.h"
#include <chrono>
#include "../../Map/Map.h"

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

bool Unit::isInsideSector(const Handle *h, double sector_angle) const
{
    double half_angle = sector_angle / 2;
    double current_direction = this -> getDirection();
    double start_angle = current_direction - half_angle;
    double end_angle = current_direction + half_angle;
    double target_handle_angle = atan(h -> getY() / h -> getX());
    if (target_handle_angle >= start_angle && target_handle_angle <= end_angle)
    {
        return true;
    }
    return false;
}


void Unit::attack(double attackRadius, double sectorAngle, double attackInterval) {
    //set attack interval of survivor

     auto t_start = std::chrono::high_resolution_clock::now();
    /*get all Handle that within radius (60 degree of the circle(radius = attack_radius, center = Coordinate(Survivor)) in front of Survivor)
    if :
        1. Handle is not invulnerable
        2. Handle is Unit
        3. attack(Survivor) > armor(Unit)
    then
    deal (attack(Survivor) - armor(Unit)) amount of attack to Unit
    */
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], attackRadius); // get all surrounding handle within attack radius

    vector<Handle*>::const_iterator it_end = list.end(); 
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) 
    {
        if (isInsideSector(*it, sectorAngle) == true) // check if it within attack sector range
        {
            if (!isInvulnerable()) //check if it is vulnerable
            {
                if ((*it) -> getCategory() == Handle::Category::UNIT) // check if it is Unit
                {
                    if (this -> getDamage() >= (*it) -> getArmor()) // check if attack > armor
                    {
                        int newHealth = this -> getHealth() - (this -> getDamage() - (*it) -> getArmor());
                        this -> setHealth(newHealth);
                    }
                }
            }
        }

    }
    while (true)
    {
    auto t_end = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<float, milli>(t_end - t_start).count() > 1 / attackInterval)
    {
        //cout << chrono::duration<float, milli>(t_end - t_start).count() << endl;
        break;
    }
    }
}