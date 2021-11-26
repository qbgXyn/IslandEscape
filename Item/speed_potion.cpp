#include "speed_potion.h"

speed_potion::speed_potion(Item::ID id, int durability) : Item(id, durability) {
    name = "speed potion";
    description = "increse your speed by";
    data = 10.0;
    duration = 20.0;
}