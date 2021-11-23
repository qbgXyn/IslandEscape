#ifndef ITEM_HANDLE_H
#define ITEM_HANDLE_H

#include "Decoration.h"
#include "../../Item/Item.h"
class Item_Handle : public Decoration {
    private:
        static const int base_max_health = 1;
        static const float base_collison_radius;
        static const double base_max_speed;
        
    public:
        explicit Item_Handle(Map *map, double x, double y, Item::ID id, int inInvulnerable = 1, int inCollisionless = 1);
        ~Item_Handle();
        Item *item;
        virtual Item* getCorrespondingItem() const;

};
#endif // ITEM_HANDLE_H
