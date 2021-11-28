#ifndef ITEM_H
#define ITEM_H
/*
Data-holding class of Item
while holding all functions into this class, we don't need to implement same variables/functions twice
*/

#include <string>

using namespace std;
class Item {
    public:
        enum class ID{
            KEY,
            TORCH,
            TORCH_LIT,
            ROCK,
            BELL,
            SWORD,
            SPEED_POTION,
            REGEN_INSTANT_POTION,
            EMPTY
        };
        ID getID() const;
        string getName() const;
        string getDescription() const;
        string getTexture() const;
        int getDurability() const;
        double getData() const;
        double getDuration() const;

        void setDurability(int durability);
        explicit Item(ID id, string name, string description, string texture, int durability, double data, double duration);
    protected:
        ID id; // the ID of an item
        string name;
        string description;
        string texture;
        int durability;
        double data;
        double duration;

};
#endif // ITEM_H
