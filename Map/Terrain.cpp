#include "Terrain.h"


bool Terrain::operator()(Map::Terrain terrain) const{
    switch (terrain)
    {
    case Map::Terrain::GRASS:
        return t.count(Map::Terrain::GRASS);
    case Map::Terrain::STONE:
        return t.count(Map::Terrain::STONE);
    case Map::Terrain::SHOAL:
        return t.count(Map::Terrain::SHOAL);
    case Map::Terrain::OCEAN:
        return t.count(Map::Terrain::OCEAN);
    case Map::Terrain::VOID:
        return t.count(Map::Terrain::VOID);
    default:
        return false;
    }
}

void Terrain::operator+=(Map::Terrain terrain) {
    switch (terrain)
    {
    case Map::Terrain::GRASS:
        t.insert(Map::Terrain::GRASS);
        break;
    case Map::Terrain::STONE:
        t.insert(Map::Terrain::STONE);
    case Map::Terrain::SHOAL:
        t.insert(Map::Terrain::SHOAL);
    case Map::Terrain::OCEAN:
        t.insert(Map::Terrain::OCEAN);
    case Map::Terrain::VOID:
        t.insert(Map::Terrain::VOID);
    default:
        break;
    }
}