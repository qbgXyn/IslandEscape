#include "Item.h"

Item::Item(Item::ID id, string name, string description, string texture, int durability, double data, double duration) : 
                        id(id), name(name), description(description), texture(texture), durability(durability), data(data), duration(duration) {

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

string Item::getTexture() const {
    return texture;
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
