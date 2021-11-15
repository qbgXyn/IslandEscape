#include "Handle/Handle.h"

class Map {

    private:
        static const int grid_radius = 8;
        double width; // x
        double height; // y
        vector<Handle> processingList; // handle wait for processing in next tick e.g. handle being attacked
        vector<Handle> List; // all handle
    public:
        Map(double width, double height);
        double getMaxWidth() const;
        double getMaxHeight() const;
};