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
        explicit Effect(Type type, double duration);
        double getDuration() const;
        double getData() const;
        Type getType() const;
    private:
        double duration;
        double data;
        Type type;
};
#endif // EFFECT_H
