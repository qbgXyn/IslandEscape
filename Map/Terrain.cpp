#include "Terrain.h"


bool Terrain::operator()(Terrain::Type terrain) const {
    return t.count(terrain);
}

void Terrain::operator+=(Terrain::Type terrain) {
    t.insert(terrain);
}