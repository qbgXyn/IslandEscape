#include "key.h"

key::key(Item::ID id, int durability) : Item(id, durability) {
    name = "key";
    description = "";
    data = 0.0;
    duration = 0.0;
}