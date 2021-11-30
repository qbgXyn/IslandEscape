#include "Item_Inventory.h"
#include "../../Map/Map.h"

Item_inventory::Item_inventory(Item *item) { //a constructor :)
    this->item = Map::copyItem(item);
}

Item_inventory::Item_inventory(Item::ID id) { //a overload constructor :)
    item = Map::createItem(id);
}

Item_inventory::~Item_inventory() { //destrcutor
    delete item;
}
