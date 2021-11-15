#include "../Handle.h"
#include "../../Effect/Effect.h"

class Unit : public Handle{
    protected:
        static const float base_damage;
        static const float base_attackInterval;
        static const float base_attack_radius;
        static const float base_armor;
        static const double base_max_speed;
        float damage;
        float attackInterval;
        float armor;
        vector<Effect> EffectList;
        explicit Unit(double x, double y);
    public:
        inline float getDamage() const {return damage;}
        inline float getArmor() const {return armor;}
        void gainAttributeFromEffect();
        virtual void attack() = 0;


};