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


double Map::getMaxWidth() const {
    return width / 2;
}

double Map::getMaxHeight() const {
    return height / 2;
}

bool Map::isCoordinateInMap(double x, double y) const {
    return (x >= 0) && (x < width) && (y >= 0) && (y < height);
}

Map::Type Map::getTypeOfGrid(double x, double y) const {
    if (isCoordinateInMap(x, y)) {
        int int_x = x / grid_radius;
        int int_y = y / grid_radius;
        return grid[int_x][int_y];
    }
    return Type::VOID;

}

bool Map::isCoordinatePathable(double x, double y) const {
    Type type = getTypeOfGrid(x, y);
    return (type == Type::LAND);
}

double Map::distanceBetweenPoints(double x1, double y1, double x2, double y2) const {
    return std::hypot(x2-x1, y2-y1);
}

vector<Handle*> Map::getHandleGroup(double x, double y, double radius) {
    vector<Handle*> result;
    vector<Handle*>::const_iterator it_end = List.end();
    for(vector<Handle*>::const_iterator it = List.begin(); it != it_end; ++it) {
        if (distanceBetweenPoints((*it)->getX(), (*it)->getY(), x, y) <= radius) {
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

bool Map::createDecoration(Decoration::Type type, double x, double y) {

    if (!isCoordinatePathable(x, y)) {
        return false;
    }

    int center_x = (x/grid_radius) * grid_radius + (grid_radius / 2);
    int center_y = (y/grid_radius) * grid_radius + (grid_radius / 2);

    Handle* handle;
    switch (type)
    {
    case Decoration::Type::HOUSE:
        handle = new House{this, center_x, center_y};
        break;
    case Decoration::Type::DOOR:
        handle = new Door{this, center_x, center_y};
        break;
    case Decoration::Type::TREE:
        handle = new Tree{this, center_x, center_y};
        break;
    case Decoration::Type::CAMPFIRE:
        handle = new Campfire{this, center_x, center_y};
        break;
    case Decoration::Type::BOAT:
        handle = new Boat{this, center_x, center_y};
        break;
    }
    List.push_back(handle);

}


bool Map::createUnit(Unit::Type type, double x, double y) {

    if (!isCoordinatePathable(x, y)) {
        return false;
    }

    Handle* handle;
    switch (type)
    {
    case Unit::Type::Survivor:
        handle = new Survivor{this, x, y};
        break;
    case Unit::Type::Ghost:
        handle = new Ghost{this, x, y};
        break;
    }
    List.push_back(handle);

}

bool Map::can_walk(double x, double y) {
    // Out of bound
    if (!isCoordinatePathable(x, y)) {
        return false;
    }

    // Walk into House, Tree
    if (get_at(x, y)->get_type()==Decoration::Type::HOUSE
    || get_at(x, y)->get_type()==Decoration::Type::TREE)
        return false;

    // Walk on Land, Door, Campfire, Boat
    return true;

}
