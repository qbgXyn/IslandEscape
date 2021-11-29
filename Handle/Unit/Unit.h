//This is the base class for surviver and ghost, but also a dervied class of handle. It contains common functions like attack and
//check handles within the circular sector. It also has visibility related functions. 
#ifndef UNIT_H
#define UNIT_H

#include "../Handle.h"
#include "../../Effect/Effect.h"

class Unit : public Handle {
    protected:
        explicit Unit(Map *map, double x, double y); //constructor

        int damage; //created as the inital variable for the functions to use. Survivor and ghost function will input their own value
        int attackInterval; //put it here so that survivor and ghost can use it
        int visible_size; // base on grid && is a square for simplicity

    public:
        float getDamage() const;  //different accessors
        void setDamage(int damage);
        virtual int getVisibleSize() const; 

        bool isGridVisible(int x, int y) const; //visibility related funcitons
        bool isHandleVisible(Handle *h) const;
        void setVisibleSize(int visible_size); 


        void attack(double attackRadius, double sectorAngle); //attack functon for player and ghost
        bool isInsideSector(const Handle *h, double sector_angle) const; //a function to check if the position of the target is inside the circular sector

};
#endif // UNIT_H
