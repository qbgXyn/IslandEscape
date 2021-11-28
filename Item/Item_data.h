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
    const string texture;
    const int durability = -1;
    const double data = 0.0;
    const double duration = 0.0;
};

namespace regen_instant_potion
{
    const string name = "instant regeneration potion";
    const string description = "instantly heal 3 hp.";
    const string texture;
    const int durability = 1;
    const double data = 3.0;
    const double duration = 0.0;
};

namespace speed_potion
{
    const string name = "speed potion";
    const string description = "increse your speed by";
    const string texture;
    const int durability = 1;
    const double data = 10.0;
    const double duration = 30.0;
};

namespace sword
{
    const string name = "sword";
    const string description = "a sword which deal 1 damage to enemy in front of you.";
    const string texture = ":/resources/images/Item/short_sword.png";
    const int durability = 150;
    const double data = 1.0;
    const double duration = 0.0;
};

namespace torch_lit
{
    const string name = "torch (lit)";
    const string description = "a torch lighten up the surronding environments. Increases your visibility by 2. decreases the durability by 1 per second.";
    const string texture = ":/resources/images/Item/torch_item_lit.gif";
    const int durability = 90*GAME_TICK;
    const double data = 3.0;
    const double duration = 0.0;
};

namespace torch
{
    const string name = "torch";
    const string description = "a torch lighten up the surronding environments. Lit it up to increase your visibility by 3.";
    const string texture = ":/resources/image/Item/torch_item.png";
    const int durability = 90*GAME_TICK;
    const double data = 3.0;
    const double duration = 0.0;
};
#endif // ITEM_DATA_H
