#include "Unit.h"
#include <chrono>
#include "../../Map/Map.h"

Unit::Unit(Map *map, double x, double y) : Handle(map, x, y) { //constructor and pass value to handle constructor
    category = Handle::Category::UNIT;
    // initially no attack cooldown
    attackInterval = 0;
}

float Unit::getDamage() const { //accessor
    return damage;
}

void Unit::setDamage(int damage) { //mutator
    this->damage = damage;
}

void Unit::setVisibleSize(int visible_size) { //mutator
    this->visible_size = visible_size;
}

bool Unit::isInsideSector(const Handle *h, double sector_angle) const //check if the target is within the circular sector
{
    double half_angle = sector_angle / 2;
    double current_direction = this->getDirection();
    double start_angle = current_direction - half_angle; //the start angle of the radius
    double end_angle = current_direction + half_angle; //end angle of the radius
    double target_handle_angle = atan2(-(h->getY()-this->getY()), (h->getX()-this->getX()))*180/PI;
    if (target_handle_angle >= start_angle && target_handle_angle <= end_angle) //return true if it is within the radius sector
    {
        return true;
    }
    return false;
}


int Unit::getVisibleSize() const { //accessor
    return visible_size;
}

bool Unit::isGridVisible(int x, int y) const { //check if the grid is visible as the player will move around. Keep calling this function to check the visible grids
    int u_x = ( static_cast<int> (location[0]) ) / map->grid_size;
    int u_y = ( static_cast<int> (location[1]) ) / map->grid_size;

    return ( abs(u_x - x) <= visible_size ) && ( abs(u_y - y) <= visible_size );
}

bool Unit::isHandleVisible(Handle *h) const { //check if the handle is visible for player
    return isGridVisible(h->getX() / map->grid_size, h->getY() / map->grid_size);
}

void Unit::attack(double attackRadius, double sectorAngle) {
    /*get all Handle that within radius (60 degree of the circle(radius = attack_radius, center = Coordinate(Survivor)) in front of Survivor) 
    This part is break down into two functions, one check handle in a given radius circle. And isInside sector function further check if the handles 
    within the circule is inside the attack sector

    if :
        1. Handle is not invulnerable
        2. attack(Survivor) > armor(Unit)
    then
    deal (attack(Survivor) - armor(Unit)) amount of attack to Unit
    */
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], attackRadius); // get all surrounding handle within attack radius

    vector<Handle*>::const_iterator it_end = list.end(); 
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) 
    {
        if (isInsideSector(*it, sectorAngle) == true) // check if it within attack sector range
        {
            if (!(*it)->isInvulnerable()) //check if it is vulnerable
            {
                if ((*it) -> getType() != this -> getType() && this != (*it)) // check if it is the same type
                {
                    if (this -> getDamage() >= (*it) -> getArmor()) // check if attack > armor
                    {
                        int newHealth = (*it)->getHealth() - (this->getDamage() - (*it)->getArmor());
                        (*it) -> setHealth(newHealth);
                    }
                }
            }
        }
    }
}
