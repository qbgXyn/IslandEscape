#include "Item_inventory.h"


Item_inventory::Item_inventory(Item::ID id, Item::Category category,string name, string description, int count, int durability, double data, double duration)
                             : id(id), category(category), description(description), count(count), durability(durability), data(data), duration(duration) {

}

double Item_inventory::getData() const {
    return data;
}

Item::ID Item_inventory::getID() const {
    return id;
}

int Item_inventory::getDurability() const {
    return durability;
}

double Item_inventory::getDuration() const {
    return duration;
}

int Item_inventory::setDurability(int durability) {
    this->durability = durability;
}