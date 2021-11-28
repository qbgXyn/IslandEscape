//This is used for setting up terrain types. And this part have very few function because terrains are mainly png and insert in graphic.cpp
#ifndef TERRAIN_H
#define TERRAIN_H

#include <set>
using namespace std;
class Terrain {
    public:
        enum class Type {
            GRASS,
            STONE,
            OCEAN,
            SHOAL,
            VOID // should not appears
        };
        set<Terrain::Type> t;
        bool operator()(Terrain::Type terrain) const;
        void operator+=(Terrain::Type terrain);
};
#endif // TERRAIN_H
