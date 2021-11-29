#include <random>
#include <cstdlib>
#include <string>


#include "Map.h"
#include "../Handle/Handle.h"

// #include "../Item/key.h"
// #include "../Item/regen_instant_potion.h"
// #include "../Item/sword.h"
// #include "../Item/torch.h"
// #include "../Item/torch_lit.h"
// #include "../Item/speed_potion.h"
#include "../Item/Item_data.h"

#include "Terrain.h"

#include <iostream>

Map::Map(double width, double height) : width(width), height(height) { //constructor:)
    int i = width/grid_size;  // width = i grids 
    int j = height/grid_size; // height = j grids

    grid = new Terrain::Type* [i]; //build the grid as the basic layer with grass
    for (int x = 0; x < i; x++) {
        grid[x] = new Terrain::Type [j];
        for (int y = 0; y < j; y++) {
            grid[x][y] = Terrain::Type::GRASS;
        }
    }
}

Map::~Map() { //destructor coz that is pointer array
    int i = width/grid_size;
    for (int x = 0; x < i; x++) {
        delete [] grid[x];
    }
    delete [] grid;
}


double Map::getMaxWidth() const { //accessor
    return width;
}

double Map::getMaxHeight() const { //accessor
    return height;
}

bool Map::isCoordinateInMap(double x, double y) const { //check if the coordinate exist
    return (x >= 0) && (x < width) && (y >= 0) && (y < height);
}

Terrain::Type Map::getTerrainOfGrid(double x, double y) const { //a convertor 
    if (isCoordinateInMap(x, y)) { 
        int i = x/grid_size;
        int j = y/grid_size;
        return grid[i][j];
    }
    return Terrain::Type::VOID; //Void type is used to return out of bound coordinate

}

double Map::getRandomDouble(double minValue, double maxValue) const { //generate random locartion
    double value = (double)rand() / RAND_MAX;
    return minValue + value * (maxValue - minValue);
}   


double Map::distanceBetweenPoints(double x1, double y1, double x2, double y2) const { //distance function
    return std::hypot(x2-x1, y2-y1);
}

vector<Handle*> Map::getHandleGroup(double x, double y, double radius) { //function to detect all surrounding handle and return a vector container
    vector<Handle*> result;
    vector<Handle*>::const_iterator it_end = List.end();
    for(vector<Handle*>::const_iterator it = List.begin(); it != it_end; ++it) { //loop through all existing handles, check if the distance is within the radius, if yes then add it into the vector container
        if (distanceBetweenPoints((*it)->getX(), (*it)->getY(), x, y) <= radius) {
            result.push_back(*it);
        }
    }
    return result;
}

Terrain::Type Map::get_at(double x, double y) const { //return the type of terrain on given grid
    if (x < 0 || x >= width)
        return Terrain::Type::VOID;
    if (y < 0 || y >= height)
        return Terrain::Type::VOID;
    return grid[(int)(x/grid_size)][(int)(y/grid_size)]; //if inside the map, return the terrain type
}


Handle* Map::createHandle(Handle::Type type, double x, double y) { //create handles for the map on given location
    Handle* handle = nullptr;
    switch (type)
    {
    case Handle::Type::SURVIVOR:
        handle = new Survivor{this, x, y};
        break;
    case Handle::Type::GHOST:
        handle = new Ghost{this, x, y};
        break;
    case Handle::Type::CHEST:
        handle = new Chest{this, x, y};
        break;
    case Handle::Type::TREE:
        handle = new Tree{this, x, y};
        break;
    case Handle::Type::CAMPFIRE:
        handle = new Campfire{this, x, y};
        break;
    case Handle::Type::BOAT:
        handle = new Boat{this, x, y};
        break;
    default:
        return nullptr;
    }

    if (handle->isCoordinateWalkable(x, y)) {
        List.push_back(handle);
        if (handle->getType() == Handle::Type::GHOST) { // also add ghost into ghostList for calling ai(), in this way we don't need to search ghost every tick
            ghostList.push_back(reinterpret_cast<Ghost*> (handle));
        }
        return handle;
    }
    delete handle;
    return nullptr;
}


bool Map::createItem_Handle(Item::ID id, double x, double y) { //create the handle list of the map
    Handle* handle = new Item_Handle{this, x, y, id};

    if (handle->isCoordinateWalkable(x, y)) { //double check to ensure that the coordinate is reasonable to put handles
        List.push_back(handle); //insert the handle
        return true;
    }
    delete handle;
    return false;
}

Item* Map::createItem(Item::ID id) { //create item
    Item * i = nullptr;
    cout << "inside createItem()" << endl;
    switch (id) //there have the constructor input of different type of item
    {
    case Item::ID::KEY:
        i = new Item {Item::ID::KEY,
                    key::name,
                    key::description,
                    key::texture,
                    key::durability,
                    key::data,
                    key::duration};
        break;
    case Item::ID::TORCH:
        i = new Item {Item::ID::TORCH,
                    torch::name,
                    torch::description,
                    torch::texture,
                    torch::durability,
                    torch::data,
                    torch::duration};
        break;
    case Item::ID::TORCH_LIT:
        i = new Item {Item::ID::TORCH_LIT,
                    torch_lit::name,
                    torch_lit::description,
                    torch_lit::texture,
                    torch_lit::durability,
                    torch_lit::data,
                    torch_lit::duration};
        break;
    case Item::ID::SWORD:
        cout << "sword founded" << endl;
        i = new Item {Item::ID::SWORD,
                    sword::name,
                    sword::description,
                    sword::texture,
                    sword::durability,
                    sword::data,
                    sword::duration};
        break;
    case Item::ID::SWORD_COOLDOWN:
        i = new Item {Item::ID::SWORD_COOLDOWN,
                    sword_cooldown::name,
                    sword_cooldown::description,
                    sword_cooldown::texture,
                    sword_cooldown::durability,
                    sword_cooldown::data,
                    sword_cooldown::duration};
        break;
    case Item::ID::ROCK:
        break;
    case Item::ID::BELL:
        break;
    case Item::ID::SPEED_POTION:
        i = new Item {Item::ID::SPEED_POTION,
                    speed_potion::name, 
                    speed_potion::description,
                    speed_potion::texture,
                    speed_potion::durability,
                    speed_potion::data,
                    speed_potion::duration};
        break;
    case Item::ID::REGEN_INSTANT_POTION:
        i = new Item {Item::ID::REGEN_INSTANT_POTION,
                    regen_instant_potion::name, 
                    regen_instant_potion::description,
                    regen_instant_potion::texture,
                    regen_instant_potion::durability,
                    regen_instant_potion::data,
                    regen_instant_potion::duration};
        break;
    default:
        break;
    }
    cout << "item created" << endl;
    return i;
}


void Map::removeHandle(Handle *h) { //remove handle from the handle list
    cout << "remove handle()" << endl;
    vector<Handle*>::const_iterator it_end = List.end();
    for(vector<Handle*>::const_iterator it = List.begin(); it != it_end; ++it) { //search and remove the handle
        cout << "iterating remove handle" << endl;
        if ((*it) == h) {
            cout << "handle founded" << endl;
            delete h;
            List.erase(it);
            return; //assuming handle is unique
        }
    }


    // List.erase(remove(List.begin(), List.end(), h), List.end());

    // List.erase(std::remove_if(List.begin(), List.end(),
    //                             [h](Handle *i) { return i && (i == h); }));
}

void Map::handleLoading()
{ 
    double randomLocationX;
    double randomLocationY;
    for (int i = 0; i < 8; i++)
    {
        if (i >= 0 && i <= 3)
        {
            while (true)
            {
                randomLocationX = getRandomLocation(0, getMaxWidth());
                randomLocationY = getRandomLocation(0, getMaxHeight());
                if (createHandle(Handle::Type::GHOST, randomLocationX, randomLocationY) != nullptr)
                {
                    break;
                }
            }
        }

        if (i >= 4)
        {
            /*while (true)
            {
                randomLocationX = getRandomLocation(0, getMaxWidth());
                randomLocationY = getRandomLocation(0, getMaxHeight());          
            }*/
        }

    }
}

int Map::getGameTime() const { //accesor
    return game_time;
}

void Map::setGameTime(int time) { //mutator
    game_time = time;
}
