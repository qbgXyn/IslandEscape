#ifndef DECORATION_H
#define DECORATION_H
/*
abstract class
*/


#include "../Handle.h"
class Decoration : public Handle {
    protected:
        Decoration(Map *map, double x, double y, int inInvulnerable = 1);


};
#endif // DECORATION_H
