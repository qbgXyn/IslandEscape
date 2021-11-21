#ifndef DECORATION_H
#define DECORATION_H

#include "../Handle.h"
class Decoration : public Handle {
    public:
        Decoration(Map *map, Category category, Type type, double x, double y, int inInvulnerable = 1);


};
#endif // DECORATION_H
