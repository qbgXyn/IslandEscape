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
        int getDurability() const;
        double getData() const;
        double getDuration() const;

        void setDurability(int durability);
    protected:
        explicit Item(ID id, int durability = 1);
    protected:
        ID id; // the ID of an item
        string name;
        string description;
        string texture_handle;
        string texture_inventory;
        int durability;
        double data;
        double duration;

};
#endif // ITEM_H
