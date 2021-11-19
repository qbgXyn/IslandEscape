#include "Map.h"

Map::Map(int width, int height) : width(width), height(height) {
    grid = new Decoration** [width];
    for (int x = 0; x < width; x++) {
        grid[x] = new Decoration* [height];
        for (int y = 0; y < height; y++) {
            grid[x][y] = nullptr;
        }
    }
}

Map::~Map() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            delete grid[x][y];
        }
        delete [] grid[x];
    }
    delete [] grid;
}

bool Map::isCoordinatePathable(double x, double y) {}

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

Decoration* Map::get_at(int x, int y) const {
    if (x < 0 || x >= width)
        return nullptr;
    if (y < 0 || y >= height)
        return nullptr;
    return grid[x][y];
}

bool Map::construct_at(Decoration::Type type, int x, int y) {
    if (x < 0 || x >= width)
        return false;
    if (y < 0 || y >= height)
        return false;

    Decoration* decoration;
    grid[x][y] = decoration;
    switch (type)
    {
    case Decoration::Type::LAND:
        decoration = new Land{this, x, y};
        break;
    case Decoration::Type::HOUSE:
        decoration = new House{this, x, y};
        break;
    case Decoration::Type::DOOR:
        decoration = new Door{this, x, y};
        break;
    case Decoration::Type::TREE:
        decoration = new Tree{this, x, y};
        break;
    case Decoration::Type::CAMPFIRE:
        decoration = new Campfire{this, x, y};
        break;
    case Decoration::Type::BOAT:
        decoration = new Boat{this, x, y};
        break;
    
    default:
        break;
    }

}

bool Map::can_walk(float x, float y) {
    // Out of bound
    if (x < 0 || x >= width)
        return false;
    if (y < 0 || y >= height)
        return false;

    // int_x int_y for map
    int int_x = static_cast<int>(x);
    int int_y = static_cast<int>(y);

    // Walk into House, Tree
    if (get_at(int_x, int_y)->get_type()==Decoration::Type::HOUSE
    || get_at(int_x, int_y)->get_type()==Decoration::Type::TREE)
        return false;

    // Walk on Land, Door, Campfire, Boat
    return true;

}
