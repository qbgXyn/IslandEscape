#ifndef HANDLE_H
#define HANDLE_H

#include <vector>
#include <cmath>
#include <string>
#include "../util.h"
using namespace std;

class Map;
class Handle {
    protected:
        double max_speed;
        double location[2];
        double velocity[2];
        int health;
        int inInvulnerable; // instead of bool, also use it as counter, i.e. if > 0, is true
        int inInvisible;    // to prevent unintended behaviour, e.g. double invisible potion with last one run out of duration
        int inCollisionless;    // for each effect run out of duration we reduce the counter by 1
        float collisionRadius;

        bool pathableList[3];

        string texture; // the picture of this handle

        Map *map;

    public:
        explicit Handle(Map *map, double x, double y);
        virtual ~Handle() = default;
    public:
        enum class Type {
            UNIT = 1,
            DECORATION = 2,
            ITEM = 3
        };

        int getHealth() const;
        double getX() const;
        double getY() const;
        double getVelocity() const;
        double getDirection() const;
        float getCollisionRadius() const;

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

    protected:
        Type type;
};
#endif // HANDLE_H
