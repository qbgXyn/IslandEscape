#include "key.h"

key::key(Item::ID id, int durability) : Item(id, durability) {
    name = "key";
    description = "a key for turn on the boat";
    data = 0.0;
    duration = 0.0;
}