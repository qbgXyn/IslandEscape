#include "Unit.h"
class Survivor : public Unit {
    public:
        explicit Survivor(double x, double y);
        void attack();
};