#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;
class Item {
    public:
        enum class ID{
            KEY,
            TORCH,
            ROCK,
            BELL,
            SPEED_POTION,
            REGEN_INSTANT_POTION
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
