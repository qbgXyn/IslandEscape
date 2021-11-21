#include "Item.h"

Item::Item(Item::ID id, int durability) : id(id), durability(durability) {

}



Item::ID Item::getID() const {
    return id;
}

string Item::getName() const {
    return name;
}
string Item::getDescription() const {
    return description;
}

int Item::getDurability() const {
    return durability;
}

double Item::getData() const {
    return data;
}
double Item::getDuration() const {
    return duration;
}


void Item::setDurability(int durability) {
    this->durability = durability;
}