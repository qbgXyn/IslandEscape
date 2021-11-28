#include "Item_Inventory.h"
#include "../../Map/Map.h"

Item_inventory::Item_inventory(Item item) { //a constructor :)
    this->item = &item;
}

Item_inventory::Item_inventory(Item::ID id) { //a overload constructor :)
    Item* i = Map::createItem(id);
    item = i;
}

Item_inventory::~Item_inventory() { //destrcutor
    delete item;
}
