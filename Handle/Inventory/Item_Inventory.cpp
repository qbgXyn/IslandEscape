#include "Item_Inventory.h"


Item_inventory::Item_inventory(Item item) {
    this->item = &item;
}

Item_inventory::~Item_inventory() {
    delete item;
}
