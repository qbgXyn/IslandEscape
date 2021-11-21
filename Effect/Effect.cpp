#include "Effect.h"

Effect::Effect(Type type, double data, double duration) : type(type), data(data), duration(duration) {
    
}


double Effect::getDuration() const {
    return duration;
}

double Effect::getData() const {
    return data;
}

Effect::Type Effect::getType() const {
    return type;
}