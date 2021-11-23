#include "Map.h"
#include "../Handle/Handle.h"

#include "../Item/key.h"
#include "../Item/regen_instant_potion.h"

Map::Map(double width, double height) : width(width), height(height) {
    int i = width/grid_radius;  // width = i grids
    int j = height/grid_radius; // height = j grids
    grid = new Terrain::Type* [i];
    for (int x = 0; x < i; x++) {
        grid[x] = new Terrain::Type [j];
        for (int y = 0; y < j; y++) {
            grid[x][y] = Terrain::Type::GRASS;
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

Terrain::Type Map::getTerrainOfGrid(double x, double y) const {
    if (isCoordinateInMap(x, y)) {
        int int_x = x / grid_radius;
        int int_y = y / grid_radius;
        return grid[int_x][int_y];
    }
    return Terrain::Type::VOID;

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

Terrain::Type Map::get_at(double x, double y) const {
    if (x < 0 || x >= width)
        return Terrain::Type::VOID;
    if (y < 0 || y >= height)
        return Terrain::Type::VOID;
    return grid[(int)(x/grid_radius)][(int)(y/grid_radius)];
}

bool Map::createDecoration(Decoration::Type type, double x, double y) {

    int center_x = (x/grid_radius) * grid_radius + (grid_radius / 2);
    int center_y = (y/grid_radius) * grid_radius + (grid_radius / 2);

    Handle* handle;
    switch (type)
    {
    case Handle::Type::HOUSE:
        handle = new House{this, center_x, center_y};
        break;
    case Handle::Type::DOOR:
        handle = new Door{this, center_x, center_y};
        break;
    case Handle::Type::TREE:
        handle = new Tree{this, center_x, center_y};
        break;
    case Handle::Type::CAMPFIRE:
        handle = new Campfire{this, center_x, center_y};
        break;
    case Handle::Type::BOAT:
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
    case Handle::Type::SURVIVOR:
        handle = new Survivor{this, x, y};
        break;
    case Handle::Type::GHOST:
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


Item* Map::createItem(Item::ID id) {
    Item * i = nullptr;
    switch (id)
    {
    case Item::ID::KEY:
        i = new key;
        break;
    case Item::ID::TORCH:
        break;
    case Item::ID::ROCK:
        break;
    case Item::ID::BELL:
        break;
    case Item::ID::SPEED_POTION:
        break;
    case Item::ID::REGEN_INSTANT_POTION:
        i = new regen_instant_potion;
        break;
    }
    return i;
}


void Map::removeHandle(Handle *h) {
    List.erase(remove(List.begin(), List.end(), h), List.end());
}
