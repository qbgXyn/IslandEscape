#include "sword.h"

sword::sword(Item::ID id, int durability) : Item(id, durability) {
    name = "sword";
    description = "a sword which deal 1 damage to enemy in front of you.";
    data = 1.0;
    duration = 0.0;
}