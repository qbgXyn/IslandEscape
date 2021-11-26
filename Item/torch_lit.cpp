#include "torch_lit.h"

torch_lit::torch_lit(Item::ID id, int durability) : Item(id, durability) {
    name = "torch (lit)";
    description = "a torch lighten up the surronding environments. Increases your visibility by 2. decreases the durability by 1 per second.";
    data = 2.0;
    duration = 0.0;
}