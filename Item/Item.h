#ifndef ITEM_H
#define ITEM_H

#include <string>
class Item {
    public:
        enum class Category{
            POTION,
            WEAPON,
            EQUIPMENT,
            SPECIAL // including key
        };
        enum class ID{
            KEY,
            TORCH,
            ROCK,
            BELL,
            SPEED_POTION,
            REGEN_INSTANT_POTION
        };
    private:
        Category category;
        ID id; // the ID of an item


};
#endif // ITEM_H
