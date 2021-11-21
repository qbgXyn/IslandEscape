#ifndef HANDLE_H
#define HANDLE_H

#include <vector>
#include <cmath>
#include <string>
#include "../util.h"
#include "../Map/Terrain.h"
using namespace std;

class Map;
class Handle {
    public:
        enum class Category {
            UNIT,
            DECORATION
        };
        enum class Type {
            SURVIVOR,
            GHOST,
            ITEM,
            BOAT,
            CAMPFIRE,
            DOOR,
            HOUSE,
            TREE
        };
    protected:
        double max_speed;
        double location[2];
        double velocity[2];
        int health;
        int inInvulnerable; // instead of bool, also use it as counter, i.e. if > 0, is true
        int inInvisible;    // to prevent unintended behaviour, e.g. double invisible potion with last one run out of duration
        int inCollisionless;    // for each effect run out of duration we reduce the counter by 1
        float collisionRadius;


        Terrain pathable;

        string texture; // the picture of this handle

        Map *map;

    public:
        explicit Handle(Map *map, double x, double y);
        ~Handle();
    public:
        int getHealth() const;
        double getX() const;
        double getY() const;
        double getVelocity() const;
        double getDirection() const;
        float getCollisionRadius() const;

        Type getType() const;
        Category getCategory() const;

        bool isInvulnerable() const;
        bool isCollisionless() const;
        bool isInvisible() const;

        void setInvulnerable();
        void setInvisible();
        void setinCollisionless();

        void move(); // every tick, we call this function for every handle to update the info

        bool hasCollision(const Handle *h) const;

        bool isCoordinatePathable(double x, double y) const;
        bool isCoordinateWalkable(double x, double y) const;


        virtual Item* getCorrespondingItem() const;

    protected:
        Type type;
        Category category;
};
#endif // HANDLE_H
