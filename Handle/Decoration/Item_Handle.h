#ifndef ITEM_HANDLE_H
#define ITEM_HANDLE_H
/*
Handle type of item, since item can present in two ways: either on the map or inside survivor's inventory
*/
#include "Decoration.h"
#include "../../Item/Item.h"
class Item_Handle : public Decoration {        
    public:
        explicit Item_Handle(Map *map, double x, double y, Item::ID id, int inInvulnerable = 1, int inCollisionless = 1);
        explicit Item_Handle(Map *map, double x, double y, Item *item, int inInvulnerable = 1, int inCollisionless = 1);
        ~Item_Handle();
        static const int base_max_health = 1;
        static const int base_collision_radius;
        static const double base_max_speed;
        Item *item;
        virtual Item* getCorrespondingItem() const;

};
#endif // ITEM_HANDLE_H
