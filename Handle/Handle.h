#include <vector>
#include <cmath>
#include "../const.h"
using namespace std;

class Handle {
    protected:
        static const float base_max_health;
        static const float base_collison_radius;
        double location[2];
        double velocity[2];
        double acceleration[2];
        float health;
        int inInvulnerable; // instead of bool, also use it as counter, i.e. if > 0, is true
        int inInvisible;    // to prevent unintended behaviour, e.g. double invisible potion with last one run out of duration
        int inCollisionless;    // for each effect run out duration we reduce the counter by 1
        double collisionRadius;

    protected:
        explicit Handle(double x, double y);
    public:
        enum class Type {
            UNIT = 1,
            DECORATION = 2,
            ITEM = 3
        };
        bool isCoordinateInMap(double x, double y);

        inline float getHealth() const {return health;}
        inline double getX() const {return location[0];}
        inline double getY() const {return location[1];}
        inline double getVelocity() const {return hypot(velocity[0], velocity[1]);}
        inline double getDirection() const {return atan2(velocity[1], velocity[0]) * 180.0 / PI;}

        inline bool isInvulnerable() const {return (inInvulnerable > 0) ? true: false;}
        inline bool isCollisionable() const {return (inCollisionless > 0) ? true: false;}
        inline bool isInvisible() const {return (inInvisible > 0) ? true: false;}

        inline void setInvulnerable() { ++inInvulnerable;}
        inline void setInvisible() { ++inInvisible;}
        inline void setinCollisionless() { ++inCollisionless;}
        void move(); // every tick, we call this function for every handle to update the info
};