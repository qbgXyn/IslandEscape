#ifndef MAP_H
#define MAP_H

// #include "../Handle/Handle.h"
// #include "../Handle/Unit/Unit.h"
// #include "../Handle/Decoration/Decoration.h"

#include "Terrain.h"

#include "../Handle/Unit/Survivor.h"
#include "../Handle/Unit/Ghost.h"

#include "../Handle/Decoration/Chest.h"
#include "../Handle/Decoration/Tree.h"
#include "../Handle/Decoration/Campfire.h"
#include "../Handle/Decoration/Boat.h"

#include "../Handle/Decoration/Item_Handle.h"

#include <string>

class Map {

    private:

        double width; // x
        double height; // y

        int game_time {30*GAME_TICK}; //seconds*50

    public:
        Map(double width, double height);
        ~Map();
        double getMaxWidth() const;
        double getMaxHeight() const;
        bool isCoordinateInMap(double x, double y) const;
        Terrain::Type getTerrainOfGrid(double x, double y) const;

        double getRandomLocation(double minValue, double maxValue) const;


        double distanceBetweenPoints(double x1, double y1, double x2, double y2) const;

        vector<Handle*> getHandleGroup(double x, double y, double radius);

        Terrain::Type get_at(double x, double y) const;
        static Item* createItem(Item::ID);
        bool createItem_Handle(Item::ID id, double x, double y);

        Handle* createHandle(Handle::Type type, double x, double y);
        void removeHandle(Handle *h);

        int getGameTime() const;
        void setGameTime(int time);
       
        Survivor* player;
        vector<Handle*> List; // all handle
        Terrain::Type** grid;
        static const int grid_size = 64; // length of a square of a grid on the map, for displaying texture only(grass, sea, etc.)
};
#endif // MAP_H
