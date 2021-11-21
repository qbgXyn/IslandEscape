#include "Terrain.h"


bool Terrain::operator()(Map::Terrain terrain) const {
    return t.count(terrain);
}

void Terrain::operator+=(Map::Terrain terrain) {
    t.insert(terrain);
}