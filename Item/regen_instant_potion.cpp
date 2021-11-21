#include "regen_instant_potion.h"

regen_instant_potion::regen_instant_potion(Item::ID id, int durability) : Item(id, durability) {
    name = "regen_instant_potion";
    description = "";
    data = 3.0;
    duration = 0.0;
}