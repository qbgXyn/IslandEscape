#include "Terrain.h"

bool Terrain::operator()(Terrain::Type terrain) const { //count number of terrain, return true if there has at least one terrain 
    return t.count(terrain);
}

void Terrain::operator+=(Terrain::Type terrain) { //insert terrain into the container
    t.insert(terrain);
}
