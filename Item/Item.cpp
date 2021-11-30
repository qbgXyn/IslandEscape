#include "Item.h"

Item::Item(Item::ID id, string name, string description, string texture, int durability, double data, double duration) : //constructor with many parameter becasue we do not have time to make many .cpp and .h:)
                        id(id), name(name), description(description), texture(texture), durability(durability), data(data), duration(duration) {

}

Item::ID Item::getID() const { //accessor
    return id;
}

string Item::getName() const { //accessor
    return name;
}
string Item::getDescription() const { //accessor
    return description;
}

string Item::getTexture() const { //accessor
    return texture;
}

int Item::getDurability() const { //accessor
    return durability;
}

double Item::getData() const { //accessor
    return data;
}
double Item::getDuration() const { //accessor
    return duration;
}

void Item::setDurability(int durability) { //mutator
    this->durability = durability;
}
