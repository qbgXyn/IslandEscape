#include "Map.h"

Map::Map(double width, double height) {

}


vector<Handle> Map::getHandleGroup(double x, double y, double radius) {
    vector<Handle> result(10);
    vector<Handle>::const_iterator it_end = List.end();
    for(vector<Handle>::const_iterator it = List.begin(); it != it_end; ++it) {
        if (distanceBetweenPoints(it->getX(), it->getY(), x, y) <= radius) {
            result.push_back(*it);
        }
    }
    return result;
}
