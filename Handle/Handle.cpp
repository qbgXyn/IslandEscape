//#include "Handle.h"
#include "../Map/Map.h"

Handle::Handle(Map *map, double x, double y) { //constructor which put handles on the location in the map
    this->map = map;
    location[0] = x;
    location[1] = y;
    armor = 0;
    health = 1;
    inInvulnerable = 0;
    inInvisible = 0;
    inCollisionless = 0;
    collisionRadius = 0;

    string texture = "";
} 

// Handle::~Handle() {
//     map->removeHandle(this);
// }

int Handle::getHealth() const { //accessor
    return health;
}

double Handle::getX() const { //accessor 
    return location[0];
}

double Handle::getY() const { //accessor
    return location[1];
}

double Handle::getVelocity() const { //accessor
    return hypot(velocity[0], velocity[1]); //make a vector from x and y
}

double Handle::getVelocityX() const { //accessor
    return velocity[0];
}

double Handle::getVelocityY() const { //accessor
    return velocity[1];
}

double Handle::getDirection() const { //accessor
    double angle = atan2(abs(velocity[1]), abs(velocity[0]))*180/PI;
    if (velocity[0] <= 0 && velocity[1] <= 0)       //vector points at left top
        angle = 180-angle;
    else if (velocity[0] <= 0 && velocity[1] >= 0)  //vector points at left bottom
        angle -= 180;
    else if (velocity[0] >= 0 && velocity[1] >= 0)  //vector points at right bottom
        angle = -angle;
    else if (velocity[0] <= 0 && velocity[1] <= 0); //vector points at left top

    return angle; //return the angle of the direction
}

float Handle::getCollisionRadius() const { //accessor
    return collisionRadius;
}

Handle::Type Handle::getType() const { //accessor
    return type;
}

Handle::Category Handle::getCategory() const { //accessor
    return category;
}

bool Handle::isInvulnerable() const { //check if invulnerable
    return (inInvulnerable > 0);
}

bool Handle::isCollisionless() const { //check if collisionless 
    return (inCollisionless > 0);
}

bool Handle::isInvisible() const { //check if visible
    return (inInvisible > 0);
}

void Handle::setInvulnerable(bool state) { //mutator
    if (state) {
        ++inInvulnerable;
    }else {
        --inInvulnerable;
    }
}

void Handle::setInvisible(bool state) { //mutator
    if (state) {
        ++inInvisible;
    }else {
        --inInvisible;
    }
}

void Handle::setinCollisionless(bool state) { //mutator
    if (state) {
        ++inCollisionless;
    }else {
        --inCollisionless;
    }
}

void Handle::setHealth(int newHealth) //mutator
{
    health = newHealth;
}

void Handle::setVelocityX(double speed) {
    velocity[0] = speed;
}

void Handle::setVelocityY(double speed) {
    velocity[1] = speed;
}

bool Handle::hasCollision(const Handle *h, double x, double y) const { //check collision
    // if one of them is collisionless
    if (h->isCollisionless() || isCollisionless()) {
        return false;
    }

    //check distance between
    double d = map->distanceBetweenPoints(x, y, h->location[0], h->location[1]);
    return ( (d - this->collisionRadius - h->collisionRadius) < 0);
}

int Handle::getArmor() const { //accessor
    return armor;
}

int Handle::getVisionRadius() const { //accessor
    return 0;
}
bool Handle::isGridVisible(int x, int y) const { //check if grid visible, only valid for Unit and it's derived class
    return false;
}
bool Handle::isHandleVisible(Handle *h) const { //check if handle visible, only valid for Unit and it's derived class
    return false;
}


void Handle::update() {
    /*
    1. get new position
    2. check collision
    3. if legal, change position, otherwise, set speed to 0

    4. if velocity > 0, and move button released, decrease velocity
    5. if max speed not reached, and move button pressed, increase velocity
    */
    double newPosition[2]; //temp array for new position

//    cout << "handle update:" << static_cast<int> (this->type) << endl;
   
    if (map->isDoubleZero(getVelocity())) { 
        return; // no need to update position since no velocity
    }

    newPosition[0] = location[0] + velocity[0]; //new position
    newPosition[1] = location[1] + velocity[1];

    // if (type == Type::SURVIVOR) {
    // cout << "position: " << location[0] << " " << location[1] << endl;
    // cout << "velocity: " << velocity[0] << " " << velocity[1] << endl;
    // cout << "newPosition: " << newPosition[0] << " " << newPosition[1] << endl;
    // }


    if (isCoordinateWalkable(newPosition[0], newPosition[1]) == true)
    {
            location[0] = newPosition[0];
            location[1] = newPosition[1]; //if new position x and y both walkable then walk to the new position
    }
    else if (isCoordinateWalkable(newPosition[0], location[1]) == true) //if horizontal is walkable only
            location[0] = newPosition[0];

    else if (isCoordinateWalkable(location[0], newPosition[1]) == true) //if only vertical is walkable
            location[1] = newPosition[1];

}

bool Handle::isCoordinatePathable(double x, double y) const { //check if pathable
    if (!map->isCoordinateInMap(x, y)) {  //check if point is inside the map
        return false;
    }

    Terrain::Type terrain = map->getTerrainOfGrid(x, y); //check if the terrain element is pathable, becasue player cannot walk on the ocean
    return pathable(terrain);
}

bool Handle::isCoordinateWalkable(double x, double y) const{
    // check if out of bound or
    // handle can be on that terrain
    if (!isCoordinatePathable(x, y)) {
        return false;
    }

    // no need to check if collisionless
    if(isCollisionless()) {
        return true;
    }

    vector<Handle*> list = map->getHandleGroup(x, y, MAX_COLLISION_RADIUS); // get all surrounding handle

    vector<Handle*>::const_iterator it_end = list.end(); // check if it collide with existing handle
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) {
        if (this != *it && hasCollision(*it, x, y)) { //if collide, then cannot walk
            return false;
        }
    }

    return true; //else can walk

}

void Handle::ChestAddItem(Item::ID id) { //add item
    return;
}

Item* Handle::getCorrespondingItem() const{ //get item
    return nullptr;
}

int Handle::getSpecies() const { //get species for tree and ghost
    return 0;
}
