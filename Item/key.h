#ifndef KEY_H
#define KEY_H

#include "Item.h"

class key : public Item{
    public:
        explicit key(Item::ID id = Item::ID::KEY, int durability = -1);
};
#endif // KEY_H
