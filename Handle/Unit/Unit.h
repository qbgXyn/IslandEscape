#ifndef UNIT_H
#define UNIT_H

#include "../Handle.h"
#include "../../Effect/Effect.h"

class Unit : public Handle {
    protected:
        int damage;
        float attackInterval;
        vector<Effect*> EffectList;
        int visible_radius;
        explicit Unit(Map *map, double x, double y);
    public:
        float getDamage() const;
        float getArmor() const;
        void gainAttributeFromEffect(Effect *e);
        void addEffect(Effect *e);
        void attack(double attackRadius, double sectorAngle, double attackInterval);
        bool isInsideSector(const Handle *h, double sector_angle) const;

};
#endif // UNIT_H
