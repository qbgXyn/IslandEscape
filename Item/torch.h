#ifndef TORCH_H
#define TORCH_H

#include "Item.h"

class torch : public Item{
    public:
        explicit torch(Item::ID id = Item::ID::TORCH, int durability = 90);
};
#endif // TORCH_H
