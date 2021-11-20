#ifndef UNIT_H
#define UNIT_H

#include "../Handle.h"
#include "../../Effect/Effect.h"

class Unit : public Handle{
    protected:
        int damage;
        float attackInterval;
        int armor;
        vector<Effect&> EffectList;
        int visible_radius;
        explicit Unit(Map *map, double x, double y);
    public:
        enum class Type {
            Survivor,
            Ghost
        };
        inline float getDamage() const {return damage;}
        inline float getArmor() const {return armor;}
        void gainAttributeFromEffect(Effect &e);
        virtual void attack() = 0;


};
#endif // UNIT_H
