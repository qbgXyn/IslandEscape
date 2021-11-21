#ifndef DECORATION_H
#define DECORATION_H

#include "../Handle.h"
class Decoration : public Handle {
    public:
        Decoration(Map *map, Category category, Type type, double x, double y, int inInvulnerable = 1);

        virtual Decoration::Type get_type() const = 0;

};
#endif // DECORATION_H
