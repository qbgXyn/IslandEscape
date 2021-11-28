#ifndef TREE_H
#define TREE_H

/*
decoration, no other usage
*/

#include "Decoration.h"

class Tree : public Decoration {
    private:
        static const int base_max_health = 10;
        static const float base_collison_radius;
        static const double base_max_speed;
    public:
        explicit Tree(Map *map, double x, double y, int inInvulnerable = 1);


};
#endif // TREE_H
