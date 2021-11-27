#include "Item_Inventory.h"
#include "../../Map/Map.h"

Item_inventory::Item_inventory(Item item) {
    this->item = &item;
}

Item_inventory::Item_inventory(Item::ID id) {
    Item* i = Map::createItem(id);
    item = i;
}

Item_inventory::~Item_inventory() {
    delete item;
}
