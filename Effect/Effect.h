class Effect {

    public:
        enum class Type {
            REGEN_INSTANT = 1,
            SPEED = 2,
            INVULNERABLE = 3,
            INVISIBLE = 4
            // for simplicity, only part of the attribute can be buffed by potion
        };
        explicit Effect(double duration);
        inline double getDuration() const {return duration;}
        inline double getData() const {return data;}
        inline Type getType() const {return type;}
        Type getAttribute() const {return type;}
    private:
        double duration;
        double data;
        Type type;
};
