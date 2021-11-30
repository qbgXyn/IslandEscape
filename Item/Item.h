#ifndef ITEM_H
#define ITEM_H
/*
//Data-holding class of Item
//while holding all functions into this class, we don't need to implement same variables/functions twice
*/

#include <string>

using namespace std;
class Item {
    public:
        enum class ID{ //different type of item
            KEY,
            TORCH,
            TORCH_LIT,
            ROCK,
            BELL,
            SWORD,
            SWORD_COOLDOWN,
            SPEED_POTION,
            REGEN_INSTANT_POTION,
            EMPTY
        };

        ID getID() const; //different accessors
        string getName() const;
        string getDescription() const;
        string getTexture() const;
        int getDurability() const;
        double getData() const;
        double getDuration() const;

        void setDurability(int durability); //mutator

        explicit Item(ID id, string name, string description, string texture, int durability, double data, double duration); //constructor

    protected:
        ID id; // the ID of an item
        string name; //base variable needed for item
        string description;
        string texture;
        int durability;
        double data;
        double duration;

};
#endif // ITEM_H
