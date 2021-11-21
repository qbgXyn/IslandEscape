#ifndef REGEN_INSTANT_POTION_H
#define REGEN_INSTANT_POTION_H

#include "Item.h"

class regen_instant_potion : public Item{
    public:
        explicit regen_instant_potion(Item::ID id = Item::ID::REGEN_INSTANT_POTION, int durability = 1);
};
#endif // REGEN_INSTANT_POTION_H
