#ifndef MAP_H
#define MAP_H

#include "../Handle/Handle.h"
#include "../Handle/Unit/Unit.h"
#include "../Handle/Decoration/Decoration.h"

#include "../Handle/Unit/Survivor.h"
#include "../Handle/Unit/Ghost.h"

#include "../Handle/Decoration/House.h"
#include "../Handle/Decoration/Door.h"
#include "../Handle/Decoration/Tree.h"
#include "../Handle/Decoration/Campfire.h"
#include "../Handle/Decoration/Boat.h"

class Map {

    private:

        static const int grid_radius = 64; // length of a square of a grid on the map, for displaying texture only(grass, sea, etc.)
        double width; // x
        double height; // y
        vector<Handle*> List; // all handle

    public:
        enum class Terrain {
            LAND,
            OCEAN,
            VOID
        };

        Map(double width, double height);
        ~Map();
        double getMaxWidth() const;
        double getMaxHeight() const;
        bool isCoordinateInMap(double x, double y) const;
        Terrain getTerrainOfGrid(double x, double y) const;


        double distanceBetweenPoints(double x1, double y1, double x2, double y2) const;

        vector<Handle*> Map::getHandleGroup(double x, double y, double radius);

        Terrain get_at(double x, double y) const;
        bool createDecoration(Decoration::Type type, double x, double y);
        bool createUnit(Unit::Type type, double x, double y);

    private:
        Terrain** grid;

};
#endif // MAP_H
