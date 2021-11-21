#ifndef ITEM_INVENTORY_H
#define ITEM_INVENTORY_H

#include <string>
#include "../../Item/Item.h"
using namespace std;
class Item_inventory {
    private:
        Item::ID id; // the ID of an item
        Item::Category category;
        string name;
        string description;
        int count;
        int durability; // -1 for permanent item
        double data;
        double duration;
    public:
        explicit Item_inventory(Item::ID id, Item::Category category,string name, string description, int count, int durability, double data, double duration);
        double getData() const;
        Item::ID getID() const;
        int getDurability() const;
        double getDuration() const;
        int setDurability(int durability);

};
#endif // ITEM_INVENTORY_H
