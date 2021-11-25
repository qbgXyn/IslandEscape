#ifndef MAP_H
#define MAP_H

// #include "../Handle/Handle.h"
// #include "../Handle/Unit/Unit.h"
// #include "../Handle/Decoration/Decoration.h"

#include "Terrain.h"

#include "../Handle/Unit/Survivor.h"
#include "../Handle/Unit/Ghost.h"

#include "../Handle/Decoration/House.h"
#include "../Handle/Decoration/Door.h"
#include "../Handle/Decoration/Tree.h"
#include "../Handle/Decoration/Campfire.h"
#include "../Handle/Decoration/Boat.h"

#include "../Handle/Decoration/Item_Handle.h"

class Map {

    private:

        static const int grid_radius = 64; // length of a square of a grid on the map, for displaying texture only(grass, sea, etc.)
        double width; // x
        double height; // y
        vector<Handle*> List; // all handle

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
        Item* createItem(Item::ID);
        bool createItem_Handle(Item::ID id, double x, double y);

        bool createHandle(Handle::Type type, double x, double y);
        void removeHandle(Handle *h);

    private:
        Terrain::Type** grid;

};
#endif // MAP_H
