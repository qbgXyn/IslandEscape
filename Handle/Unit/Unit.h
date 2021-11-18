#include "../Handle.h"
#include "../../Effect/Effect.h"

class Unit : public Handle{
    protected:
        static const float base_damage;
        static const float base_attackInterval;
        static const float base_attack_radius;
        static const float base_armor;
        float damage;
        float attackInterval;
        float armor;
        vector<Effect> EffectList;
        explicit Unit(Map *map, double x, double y);
    public:
        inline float getDamage() const {return damage;}
        inline float getArmor() const {return armor;}
        void gainAttributeFromEffect(Effect &e);
        virtual void attack();


};
