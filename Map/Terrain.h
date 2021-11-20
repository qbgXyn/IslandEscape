#include <string>
#include <set>
#include "Map.h"
using namespace std;
class Terrain {
    public:
        set<Map::Terrain> t;
        bool operator()(Map::Terrain terrain) const;
        void operator+=(Map::Terrain terrain);
};