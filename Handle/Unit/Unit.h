#include "../Handle.h"
#include "../../Effect/Effect.h"

class Unit : public Handle{
    protected:
        int damage;
        float attackInterval;
        int armor;
        vector<Effect> EffectList;
        explicit Unit(Map *map, double x, double y);
    public:
        inline float getDamage() const {return damage;}
        inline float getArmor() const {return armor;}
        void gainAttributeFromEffect(Effect &e);
        virtual void attack() = 0;


};
