#include "Map.h"

Map::Map(double width, double height) : width(width), height(height) {
    int i = width/grid_radius;  // width = i grids
    int j = height/grid_radius; // height = j grids
    grid = new Terrain* [i];
    for (int x = 0; x < i; x++) {
        grid[x] = new Terrain [j];
        for (int y = 0; y < j; y++) {
            grid[x][y] = Terrain::GRASS;
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

Map::Terrain Map::getTerrainOfGrid(double x, double y) const {
    if (isCoordinateInMap(x, y)) {
        int int_x = x / grid_radius;
        int int_y = y / grid_radius;
        return grid[int_x][int_y];
    }
    return Terrain::VOID;

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

Map::Terrain Map::get_at(double x, double y) const {
    if (x < 0 || x >= width)
        return Terrain::VOID;
    if (y < 0 || y >= height)
        return Terrain::VOID;
    return grid[(int)(x/grid_radius)][(int)(y/grid_radius)];
}

bool Map::createDecoration(Decoration::Type type, double x, double y) {

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
    
    if (handle->isCoordinateWalkable(x, y)) {
        List.push_back(handle);
        return true;
    }
    delete handle;
    return false;

}


bool Map::createUnit(Unit::Type type, double x, double y) {
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

    if (handle->isCoordinateWalkable(x, y)) {
        List.push_back(handle);
        return true;
    }
    delete handle;
    return false;
}


