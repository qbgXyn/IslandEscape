#ifndef SPEED_POTION_POTION_H
#define SPEED_POTION_POTION_H

#include "Item.h"

class speed_potion : public Item{
    public:
        explicit speed_potion(Item::ID id = Item::ID::SPEED_POTION, int durability = 1);
};
#endif // SPEED_POTION_POTION_H
