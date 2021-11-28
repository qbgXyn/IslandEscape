#ifndef UNIT_H
#define UNIT_H

#include "../Handle.h"
#include "../../Effect/Effect.h"

class Unit : public Handle {
    protected:
        int damage;
        float attackInterval;
        vector<Effect*> EffectList;
        int visible_size; // base on grid && is a square for simplicity
        explicit Unit(Map *map, double x, double y);
    public:
        float getDamage() const;
        void setDamage(int damage);
        virtual float getArmor() const;
        virtual int getVisibleSize() const;
        virtual bool isGridVisible(int x, int y) const;
        virtual bool isHandleVisible(Handle *h) const;
        void setVisibleSize(int visible_size);
        void gainAttributeFromEffect(Effect *e);
        void addEffect(Effect *e);
        void attack(double attackRadius, double sectorAngle, double attackInterval);
        bool isInsideSector(const Handle *h, double sector_angle) const;

};
#endif // UNIT_H
