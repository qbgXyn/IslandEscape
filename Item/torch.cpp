#include "torch.h"

torch::torch(Item::ID id, int durability) : Item(id, durability) {
    name = "torch";
    description = "a torch lighten up the surronding environments. Lit it up to increase your visibility by 2.";
    data = 3.0;
    duration = 0.0;
}