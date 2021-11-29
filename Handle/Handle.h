//This is the base class of all objects appear on the map. It includes dervied classes of decoration which enrich the map,
//inventory will link to items which player can use to increase visibility and attack damage. It also has units which are survivor
// and ghost and they are the main characters of the game
#ifndef HANDLE_H
#define HANDLE_H

#include <vector>
#include <cmath>
#include <string>
#include "../util.h"
#include "../Map/Terrain.h"
#include "../Item/Item.h"
using namespace std;

class Map;
class Handle {
    public:
        enum class Category { //define handles into two categories
            UNIT,
            DECORATION
        };

        enum class Type { //unit has survivor and ghosr type and decoration contain the remainings
            SURVIVOR,
            GHOST,
            ITEM,
            BOAT,
            CAMPFIRE,
            CHEST,
            TREE
        };
    protected:
        double location[2]; //we use x y vector to make the location so that it can walk smoothly rather than jump from grid to grid
        double velocity[2] = {0,0}; //we use velocity vector as well such that the movement is smooth

        double max_speed;
        int health;
        int armor; //base index for handle and can be access by dervied class easily

        int inInvulnerable; // instead of bool, also use it as counter, i.e. if > 0, is true
        int inInvisible;    // to prevent unintended behaviour, e.g. double invisible potion with last one run out of duration
        int inCollisionless;    // for each effect run out of duration we reduce the counter by 1
        float collisionRadius;


        Terrain pathable;

        string texture; // the picture of this handle

        Map *map; //becasue it has to put inside the map

    public:
        explicit Handle(Map *map, double x, double y); //constructor
        virtual ~Handle() = default; //default destructor  

    public:
        int getHealth() const; //accessor

        double getX() const; //accessor for location and velocity
        double getY() const;
        double getVelocity() const;
        double getDirection() const;

        float getCollisionRadius() const; //accessor for collision radius

        Type getType() const; //accessor
        Category getCategory() const; 

        bool isInvulnerable() const; //check if handle is invulnerable 
        bool isCollisionless() const; //check if it can collision
        bool isInvisible() const; //check if visible

        void setInvulnerable(bool state); //mutator
        void setInvisible(bool state); 
        void setinCollisionless(bool state);
        void setHealth (int newHealth);
        void setVelocityX(double speed) {velocity[0] = speed;}
        void setVelocityY(double speed) {velocity[1] = speed;}

        void update(); // every tick, we call this function for every handle to update the info

        bool hasCollision(const Handle *h) const;

        int getArmor() const; //accessor
        virtual int getVisionRadius() const;

        virtual bool isGridVisible(int x, int y) const; //check if grid is visible
        virtual bool isHandleVisible(Handle *h) const; //check if handle is visible

        bool isCoordinatePathable(double x, double y) const; //two functions to check if the new position from adding direction and velocity vectors is walkable 
        bool isCoordinateWalkable(double x, double y) const;

        virtual void ChestAddItem(Item::ID id); //to add new item

    protected:
        Type type; //type and catoregy classes
        Category category;
};
#endif // HANDLE_H
