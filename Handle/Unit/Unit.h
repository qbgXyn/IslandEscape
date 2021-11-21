#ifndef UNIT_H
#define UNIT_H

#include "../Handle.h"
#include "../../Effect/Effect.h"
#include "../Inventory/Item_inventory.h"

class Unit : public Handle{
    protected:
        int damage;
        float attackInterval;
        int armor;
        vector<Effect*> EffectList;
        int visible_radius;
        explicit Unit(Map *map, double x, double y);
    public:
        inline float getDamage() const {return damage;}
        inline float getArmor() const {return armor;}
        void gainAttributeFromEffect(Effect *e);
        void addEffect(Effect *e);
        virtual void attack() = 0;
        bool insideSector(const Handle *h, double sector_angle) const;

};
#endif // UNIT_H
