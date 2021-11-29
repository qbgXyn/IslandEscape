#ifndef EFFECT_H
#define EFFECT_H

class Effect {

    public:
        enum class Type {
            REGEN_INSTANT,
            SPEED,
            INVULNERABLE,
            INVISIBLE
            // for simplicity, only part of the attribute can be buffed by potion
        };
        explicit Effect(Type type, double data, int duration);
        Type getType() const;
        double getData() const;
        int getDuration() const;
        void setDuration(int duration);
    private:
        Type type;
        double data;
        int duration;
};
#endif // EFFECT_H
