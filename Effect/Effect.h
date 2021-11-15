class Effect {
    private:
        double duration;
        enum class Type {
            REGEN = 1,
            SPEED = 2,
            INVULNERABLE = 3,
            INVISIBLE = 4
            // for simplicity, only part of the attribute can be buffed by potion
        };
        Type type;
    public:
        explicit Effect(double duration);
        inline double getDuration() const {return duration;}
        Type getAttribute() const {return type;}
};