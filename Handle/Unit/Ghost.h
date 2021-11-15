#include "Unit.h"

class Ghost : public Unit {
    public:
        explicit Ghost(double x, double y);
        void attack();
        void patrol();

};