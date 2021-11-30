//This is used for storing and displaying the item information
#ifndef ITEM_DATA_H
#define ITEM_DATA_H

#include <string>
#include "../util.h"
using namespace std;
namespace key
{
    const string name = "key";
    const string description = "a key for turn on the boat";
    const string texture = ":/resources/images/Item/key.png";
    const int durability = -1;
    const double data = 0.0;
    const int duration = 0;
};

namespace regen_instant_potion
{
    const string name = "instant regeneration potion";
    const string description = "instantly heal 3 hp.";
    const string texture = ":/resources/images/Item/potions/pt1.png";
    const int durability = 1;
    const double data = 3.0;
    const int duration = 0;
};

namespace speed_potion
{
    const string name = "speed potion";
    const string description = "increse your speed by 20";
    const string texture = ":/resources/images/Item/potions/pt3.png";
    const int durability = 1;
    const double data = 20.0;
    const int duration = 30*GAME_TICK;
};

namespace sword
{
    const string name = "sword";
    const string description = "a sword which deal 2 damage to enemy in front of you.";
    const string texture = ":/resources/images/Item/short_sword.png";
    const int durability = 150*GAME_TICK;
    const double data = 2.0;
    const int duration = 1*GAME_TICK; // attack cooldown
};

namespace sword_cooldown
{
    const string name = "sword (cooldown)";
    const string description = "a sword which deal 1 damage to enemy in front of you.";
    const string texture = ":/resources/images/Item/short_sword_cooldown.png";
    const int durability = sword::durability;
    const double data = sword::data;
    const int duration = sword::duration;
};

namespace torch
{
    const string name = "torch";
    const string description = "a torch lighten up the surronding environments. Lit it up to increase your visibility by 3.";
    const string texture = ":/resources/images/Item/torch_item.png";
    const int durability = 90*GAME_TICK;
    const double data = 3.0;
    const int duration = 0;
};

namespace torch_lit
{
    const string name = "torch (lit)";
    const string description = "a torch lighten up the surronding environments. Increases your visibility by 3. decreases the durability by 1 per second.";
    const string texture = ":/resources/images/Item/torch_lit01.png";
    const int durability = torch::durability;
    const double data = torch::data;
    const int duration = torch::duration;
};


#endif // ITEM_DATA_H
