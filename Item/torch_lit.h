#ifndef TORCH_LIT_H
#define TORCH_LIT_H

#include "Item.h"
#include "../util.h"

class torch_lit : public Item{
    public:
        explicit torch_lit(Item::ID id = Item::ID::TORCH_LIT, int durability = 90*GAME_TICK);
};
#endif // TORCH_LIT_H
