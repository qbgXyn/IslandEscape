#ifndef TREE_H
#define TREE_H

/*
decoration, no other usage
*/

#include "Decoration.h"

class Tree : public Decoration {
    private:
        int species;
    public:
        explicit Tree(Map *map, double x, double y, int type, int inInvulnerable = 1);
        static const int base_max_health = 10;
        static const int base_collision_radius;
        static const double base_max_speed;

        virtual int getSpecies() const override {return species;}

};
#endif // TREE_H
