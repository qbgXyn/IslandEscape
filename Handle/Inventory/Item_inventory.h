#include <string>
#include "../../Item/Item.h"
using namespace std;
class Item_inventory {
    private:
        int count;
        int durability;
        Item::Category category;
        Item::Type type; // the ID of an item
        string name;
        string description;


};