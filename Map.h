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
        Decoration*** grid;
        static const int grid_radius = 8; // length of a square of a grid on the map, for displaying texture only(grass, sea, etc.)
        int width; // x
        int height; // y
        vector<Handle&> List; // all handle
    public:
        Map(int width, int height);
        inline double getMaxWidth() const {return width / 2;}
        inline double getMaxHeight() const {return height / 2;}
        inline bool isCoordinateInMap(double x, double y) {return (x >= 0) && (x < width) && (y >= 0) && (y < height);}
        bool isCoordinatePathable(double x, double y);

        inline double distanceBetweenPoints(double x1, double y1, double x2, double y2) {return std::hypot(x2-x1, y2-y1);}

        vector<Handle&> getHandleGroup(double x, double y, double radius);

        bool hasCollision(const Handle &h, double x, double y);

        Decoration* get_at(int x, int y) const;
        bool construct_at(Decoration::Type type, int x, int y);
        bool can_walk(float x, float y);  

};
