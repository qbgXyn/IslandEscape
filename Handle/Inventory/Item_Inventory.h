#ifndef ITEM_INVENTORY_H
#define ITEM_INVENTORY_H
/*
inventory type of item, since item can present in two ways: either on the map or inside survivor's inventory
*/
#include <string>
#include "../../Item/Item.h"
using namespace std;
class Item_inventory {
    public:
        explicit Item_inventory(Item item);
        explicit Item_inventory(Item::ID id);
        ~Item_inventory();
        Item *item;

};
#endif // ITEM_INVENTORY_H
