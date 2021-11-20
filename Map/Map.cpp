#include "Map.h"

Map::Map(double width, double height) : width(width), height(height) {
    int i = width/grid_radius;  // width = i grids
    int j = height/grid_radius; // height = j grids
    grid = new Type* [i];
    for (int x = 0; x < i; x++) {
        grid[x] = new Type [j];
        for (int y = 0; y < j; y++) {
            grid[x][y] = Type::LAND;
        }
    }
}

Map::~Map() {
    int i = width/grid_radius;
    int j = height/grid_radius;
    for (int x = 0; x < i; x++) {
        delete [] grid[x];
    }
    delete [] grid;
}

bool Map::isCoordinatePathable(double x, double y) {

}

vector<Handle&> Map::getHandleGroup(double x, double y, double radius) {
    vector<Handle&> result;
    vector<Handle&>::const_iterator it_end = List.end();
    for(vector<Handle&>::const_iterator it = List.begin(); it != it_end; ++it) {
        if (distanceBetweenPoints(it->getX(), it->getY(), x, y) <= radius) {
            result.push_back(*it);
        }
    }
    return result;
}

Map::Type Map::get_at(double x, double y) const {
    if (x < 0 || x >= width)
        return Type::VOID;
    if (y < 0 || y >= height)
        return Type::VOID;
    return grid[(int)(x/grid_radius)][(int)(y/grid_radius)];
}

bool Map::construct_at(Decoration::Type type, double x, double y) {
    if (x < 0 || x >= width)
        return false;
    if (y < 0 || y >= height)
        return false;

    int i = x/grid_radius;
    int j = y/grid_radius;

    Handle* handle;

    switch (type)
    {
    case Decoration::Type::HOUSE:
        handle = new House{this, x, y};
        break;
    case Decoration::Type::DOOR:
        handle = new Door{this, x, y};
        break;
    case Decoration::Type::TREE:
        handle = new Tree{this, x, y};
        break;
    case Decoration::Type::CAMPFIRE:
        handle = new Campfire{this, x, y};
        break;
    case Decoration::Type::BOAT:
        handle = new Boat{this, x, y};
        break;
    default:
        break;
    }

}

bool Map::can_walk(double x, double y) {
    // Out of bound
    if (x < 0 || x >= width)
        return false;
    if (y < 0 || y >= height)
        return false;

    // Walk into House, Tree
    if (get_at(x, y)->get_type()==Decoration::Type::HOUSE
    || get_at(x, y)->get_type()==Decoration::Type::TREE)
        return false;

    // Walk on Land, Door, Campfire, Boat
    return true;

}
