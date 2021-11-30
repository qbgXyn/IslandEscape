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

#include <QFileDialog>
#include <QTextStream>
#include <QStringList>

Map::Map(double width, double height, QString filePath, QString HandleFilePath) : width(width), height(height) { //constructor:)
    int i = width/grid_size;  // width = i grids 
    int j = height/grid_size; // height = j grids

    grid = new Terrain::Type* [i]; //build the grid as the basic layer with grass
    for (int x = 0; x < i; x++) {
        grid[x] = new Terrain::Type [j];
        for (int y = 0; y < j; y++) {
            grid[x][y] = Terrain::Type::GRASS;
        }
    }

    // Load file to create Terrain for Map
    QFile file(filePath);
    QStringList numlist;
    QString match;

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    while(!file.atEnd())
    {
        match = file.readLine();
        numlist << match.split(' ');
    }
    file.close();
    int x = 0, y = 0;
    foreach(QString num, numlist) {
        grid[x][y] = static_cast<Terrain::Type>(num.toInt());
        ++x;
        if (x == i) {
            ++y;
            x = 0;
        }
    }

    // Create Player
    player = reinterpret_cast<Survivor*>(createHandle(Handle::Type::SURVIVOR, 320, 320));

    // Create Decorations
    /*createHandle(Handle::Type::BOAT, 2*64, 11*64/2);
    createHandle(Handle::Type::CAMPFIRE, 10*64-32, 10*64-32);
    createHandle(Handle::Type::CHEST, 7*64-32, 5*64-32);
    createHandle(Handle::Type::TREE, 2*64-32, 2*64-32);
    createHandle(Handle::Type::TREE, 4*64-32, 2*64-32);
    createHandle(Handle::Type::TREE, 2*64-32, 4*64-32);
    createHandle(Handle::Type::TREE, 4*64-32, 4*64-32);
    createItem_Handle(Item::ID::KEY, 12*64-32, 12*64-32);
    createHandle(Handle::Type::GHOST, 400, 400);*/

    loadHandleList(HandleFilePath);
    // for (int i = 0; i < height; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         cout << array[j][i] << " ";
    //     }
    //     cout << endl;
    // }
}

Map::~Map() { //destructor coz that is pointer array
    int i = width/grid_size;
    for (int x = 0; x < i; x++) {
        delete [] grid[x];
    }
    delete [] grid;
}



void Map::mapUpdate() {
    Handle *h;
    vector<Handle*>::const_iterator it_end = List.end(); 
    for(vector<Handle*>::const_iterator it = List.begin(); it != it_end; ++it) { //loop through all existing handles, check if the distance is within the radius, if yes then add it into the vector container
        h = *it;
       h->update();
        if (h->getHealth() <= 0) {
            removeHandle(h);
        }
    }
}


void Map::end_game() {
    win = true;
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

bool Map::isDoubleZero(double d) const {
    return (d <= ECLIPSE && d >= -ECLIPSE);
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
        handle = new Ghost{this, x, y, ghost_species};
        ghost_species = (ghost_species+1)%4;
        break;
    case Handle::Type::CHEST:
        handle = new Chest{this, x, y};
        break;
    case Handle::Type::TREE:
        handle = new Tree{this, x, y, tree_species};
        tree_species = (tree_species+1)%4;
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


Item_Handle* Map::createItem_Handle(Item::ID id, double x, double y) { //create the handle list of the map)
    Item_Handle* handle = new Item_Handle{this, x, y, id};
    // no need to check if walkable assuming only create by survivor, and walkable condition is more strict of survivor than item_handle
    List.push_back(handle); //insert the handle
    return handle;
}

Item_Handle* Map::createItem_Handle(Item *item, double x, double y) { //create the handle list of the map)
    Item_Handle* handle = new Item_Handle{this, x, y, item};
    // no need to check if walkable assuming only create by survivor, and walkable condition is more strict of survivor than item_handle
    List.push_back(handle); //insert the handle
    return handle;
}

Item* Map::createItem(Item::ID id) { //create item
    Item * i = nullptr;
    //cout << "inside createItem()" << endl;
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
        //cout << "sword founded" << endl;
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
    //cout << "item created" << endl;
    return i;
}

//deep copy of an item
Item* Map::copyItem(Item* item) {
    Item* newItem = new Item {item->getID(), item->getName(), item->getDescription(), item->getTexture(), item->getDurability(), item->getData(), item->getDuration()};
    return newItem;
}


void Map::removeHandle(Handle *h) { //remove handle from the handle list
    //cout << "remove handle()" << endl;
    vector<Handle*>::const_iterator it_end = List.end();
    for(vector<Handle*>::const_iterator it = List.begin(); it != it_end; ++it) { //search and remove the handle
        //cout << "iterating remove handle" << endl;
        if ((*it) == h) {
            //cout << "handle founded" << endl;
            List.erase(it);
            delete h;
            return; //assuming handle is unique
        }
    }
}

void Map::handleLoading()
{ 
    // randomly create a boat
    double randomLocationX;
    double randomLocationY;
    Handle* boat;
    while (true)
    {
        randomLocationX = getRandomDouble(0, width);
        randomLocationY = getRandomDouble(0, height);
        boat = createHandle(Handle::Type::BOAT, randomLocationX, randomLocationY);
        if (boat != nullptr)
        {
            break;
        }
    }

    int counter = 0; // total num of chest
    vector<Handle*> result;
    vector<Handle*>::const_iterator it_end = List.end();
    for(vector<Handle*>::const_iterator it = List.begin(); it != it_end; ++it) { //loop through all existing handles, check if it's chest
        if ((*it)->getType() == Handle::Type::CHEST) {
            result.push_back(*it);
            ++counter;
        }
    }

    int keyChest = static_cast<int> ( getRandomDouble(0, counter) ); // get a random index of the chest list
    counter = 0; // re-use counter 
    it_end = result.end();
    for(vector<Handle*>::const_iterator it = result.begin(); it != it_end; ++it) { //loop through all existing handles, check if is the index chest
        if (counter != keyChest) {
            ++counter;
        }else {
            (*it)->ChestAddItem(Item::ID::KEY);
            break;
        }
    }
    


    /*
    double randomLocationX;
    double randomLocationY;
    int n{9};
    for (int i = 0; i < n; i++)
    {
        if (i >= 0 && i <= 4)
        {
            while (true)
            {
                randomLocationX = getRandomDouble(0, getMaxWidth());
                randomLocationY = getRandomDouble(0, getMaxHeight());
                Handle* newGhost = createHandle(Handle::Type::GHOST, randomLocationX, randomLocationY);
                if (newGhost != nullptr)
                {
                    break;
                }
            }
        } 

        if (i == 5)
        {
            while (true)
            {
                randomLocationX = getRandomDouble(0, getMaxWidth());
                randomLocationY = getRandomDouble(0, getMaxHeight()); 
                Chest* newKeyChest = reinterpret_cast<Chest*> (createHandle(Handle::Type::CHEST, randomLocationX, randomLocationY));
                if (newKeyChest != nullptr)
                {
                    newKeyChest->ChestAddItem(Item::ID::KEY);
                    break;
                } 
            }
        }

        if (i >= 6)
        {
            int x = (i - 6) % 3;
            if (x == 0)
            {
                while (true)
                {
                    randomLocationX = getRandomDouble(0, getMaxWidth());
                    randomLocationY = getRandomDouble(0, getMaxHeight()); 
                    Chest* newSpeedPotionChest = reinterpret_cast<Chest*> (createHandle(Handle::Type::CHEST, randomLocationX, randomLocationY));
                    if (newSpeedPotionChest != nullptr)
                {
                    newSpeedPotionChest->ChestAddItem(Item::ID::SPEED_POTION);
                    break;
                }    
                }
            }
            if (x == 1)
            {
                while (true)
                {
                    randomLocationX = getRandomDouble(0, getMaxWidth());
                    randomLocationY = getRandomDouble(0, getMaxHeight()); 
                    Chest* newRegenPotionChest = reinterpret_cast<Chest*> (createHandle(Handle::Type::CHEST, randomLocationX, randomLocationY));
                    if (newRegenPotionChest != nullptr)
                {
                    newRegenPotionChest->ChestAddItem(Item::ID::REGEN_INSTANT_POTION);
                    break;
                }    
                }
            }

            if (x == 2)
            {
                while (true)
                {
                    randomLocationX = getRandomDouble(0, getMaxWidth());
                    randomLocationY = getRandomDouble(0, getMaxHeight()); 
                    Handle* newEmptyChest = createHandle(Handle::Type::CHEST, randomLocationX, randomLocationY);
                    if (newEmptyChest != nullptr)
                {
                    break;
                }    
                }
            }

        }

    }
    */
}


void Map::loadHandleList(QString filePath)
{
  // Load file to create Handles for Map
    QFile file(filePath);
    QStringList numlist;
    QString match;

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    while(!file.atEnd())
    {
        match = file.readLine();
//        qDebug() << match;
        numlist << match.split(' ');
    }
    file.close();
    // qDebug() << numlist;
    foreach(QString num, numlist) {
        Handle::Type type;
        // std::cout << num.toInt();
        type = static_cast<Handle::Type>(num.toInt());
        switch(type)
        {
            case Handle::Type::SURVIVOR:
                map->player = createHandle(type, num.toInt(), num.toInt());
                break;
            case Handle::Type::GHOST:
            case Handle::Type::BOAT:
            case Handle::Type::TREE:
            case Handle::Type::CAMPFIRE:
            createHandle(type, num.toInt(), num.toInt());
            break;

            case Handle::Type::CHEST:
            Handle* Chest;
            Chest = createHandle(type, num.toInt(), num.toInt());
            for (int i = 0; i < 9; i++)
            {
                Item::ID itemType = static_cast<Item::ID>(num.toInt());
                Chest->ChestAddItem(itemType);
            }
            break;
            default:
                break;
        }
    }
}

int Map::getGameTime() const { //accesor
    return game_time;
}

void Map::setGameTime(int time) { //mutator
    game_time = time;
}
