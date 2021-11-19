#ifndef MAP_H
#define MAP_H

#include "Handle/Handle.h"
#include "Handle/Decoration/Decoration.h"
#include "Handle/Decoration/Land.h"
#include "Handle/Decoration/House.h"
#include "Handle/Decoration/Door.h"
#include "Handle/Decoration/Tree.h"
#include "Handle/Decoration/Campfire.h"
#include "Handle/Decoration/Boat.h"

class Map {

    private:

        Handle*** grid;
        static const int grid_radius = 64; // length of a square of a grid on the map, for displaying texture only(grass, sea, etc.)
        double width; // x
        double height; // y
        vector<Handle&> List; // all handle

    public:

        Map(double width, double height);
        ~Map();
        inline double getMaxWidth() const {return width / 2;}
        inline double getMaxHeight() const {return height / 2;}
        inline bool isCoordinateInMap(double x, double y) {return (x >= 0) && (x < width) && (y >= 0) && (y < height);}
        bool isCoordinatePathable(double x, double y);

        inline double distanceBetweenPoints(double x1, double y1, double x2, double y2) {return std::hypot(x2-x1, y2-y1);}

        vector<Handle&> Map::getHandleGroup(double x, double y, double radius);

        Handle* get_at(double x, double y) const;
        bool construct_at(Decoration::Type type, double x, double y);
        bool can_walk(double x, double y);

};
#endif // MAP_H
