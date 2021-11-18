#include <vector>
#include <cmath>
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

        Map *map;

    protected:
        explicit Handle(Map *map, double x, double y);
    public:
        enum class Type {
            UNIT = 1,
            DECORATION = 2,
            ITEM = 3
        };

        inline int getHealth() const {return health;}
        inline double getX() const {return location[0];}
        inline double getY() const {return location[1];}
        inline double getVelocity() const {return hypot(velocity[0], velocity[1]);}
        inline double getDirection() const {return atan2(velocity[1], velocity[0]) * 180.0 / PI;}
        inline virtual float getCollisionRadius() const {return collisionRadius;}

        inline bool isInvulnerable() const {return (inInvulnerable > 0) ? true: false;}
        inline bool isCollisionless() const {return (inCollisionless > 0) ? true: false;}
        inline bool isInvisible() const {return (inInvisible > 0) ? true: false;}

        inline void setInvulnerable() { ++inInvulnerable;}
        inline void setInvisible() { ++inInvisible;}
        inline void setinCollisionless() { ++inCollisionless;}

        void move(); // every tick, we call this function for every handle to update the info

        bool hasCollision(const Handle &h);
};
