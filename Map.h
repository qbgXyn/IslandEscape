#include "Handle/Handle.h"

class Map {

    private:
        static const int grid_radius = 8; // length of a square of a grid on the map, for displaying texture only(grass, sea, etc.)
        double width; // x
        double height; // y
        vector<Handle> List; // all handle
    public:
        Map(double width, double height);
        double getMaxWidth() const;
        double getMaxHeight() const;
};
