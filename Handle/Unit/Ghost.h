#include "Unit.h"

class Ghost : public Unit {
    private:
        Unit *chasing_target;
    public:
        explicit Ghost(double x, double y, Unit *chasing_target);
        void attack();
        void patrol();

};