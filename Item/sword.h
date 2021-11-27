#ifndef SWORD_H
#define SWORD_H

#include "Item.h"

class sword : public Item{
    public:
        explicit sword(Item::ID id = Item::ID::SWORD, int durability = 150);
};
#endif // SWORD_H
