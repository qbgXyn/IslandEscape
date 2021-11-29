#include "Effect.h"

Effect::Effect(Type type, double data, int duration) : type(type), data(data), duration(duration) {
    
}


int Effect::getDuration() const {
    return duration;
}

double Effect::getData() const {
    return data;
}

Effect::Type Effect::getType() const {
    return type;
}

void Effect::setDuration(int duration) {
    this->duration = duration;
}