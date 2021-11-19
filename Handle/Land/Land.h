#ifndef LAND_H
#define LAND_H

#include "../Handle.h"

class Land : public Handle {
    public:
        explicit Land(Map *map, double x, double y, int inInvulnerable = 1);

};
#endif // LAND_H
