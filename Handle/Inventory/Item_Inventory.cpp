#include "Item_Inventory.h"
#include "../../Map/Map.h"
#include <iostream>

Item_inventory::Item_inventory(Item *item) { //a constructor :)
    //std::cout << "insided item_inventory contor" << std::endl;
    this->item = Map::copyItem(item);
}

Item_inventory::Item_inventory(Item::ID id) { //a overload constructor :)
    item = Map::createItem(id);
}

Item_inventory::~Item_inventory() { //destrcutor
    delete item;
}
