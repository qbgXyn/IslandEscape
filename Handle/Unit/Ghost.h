//This is the ghost part which will patrol around and player need to aviod or attack and kill the ghost. It is also a derived class
//of unit as it used the attack function and get nearby handle function in unit. The movement of the ghost is setted as AI, when
//it detects player within the detect radius, it will start chasing and deal damage if within attack sector. 
#ifndef GHOST_H
#define GHOST_H

#include "Unit.h"

class Ghost : public Unit {
    private:
        Handle *chasing_target;

        // given a coordinate, randomly pick a coordinate within a radius centered at patrolCenter
        // once reach that random coordinate, pick another coordinate and move to that point
        // if survivor get into visible range, chase that unit
        // if the ghost leave the chasingRadius centered at patrolCenter, back to patrolCenter
        // before arrived patrolCenter, ghost will no longer chase a unit
        double patrolCenterLocation[2]; // coordinate of center
        double randomTargetLocation[2];
    public:
        explicit Ghost(Map *map, double x, double y, Handle *chasing_target = nullptr); //ghost constructor
        static const int base_max_health = 5; //ghost basic index
        static const float base_collison_radius; //ghost basic index
        static const double base_max_speed; //ghost basic index

        static const int base_damage = 1; //ghost basic index
        static const float base_attackInterval; //ghost basic index
        static const float base_attack_radius; //ghost basic index
        static const double base_attack_sector_angle; //ghost basic index
        static const int base_armor = 1; //ghost basic index
        static const int base_visible_size = 3; //ghost basic index

        static const double patrolRadius; //setting for ghost patrol
        static const double detectRadius; //setting for ghost detect area
        static const double chasingRadius; //setting for following the player


        void patrol(); //patrol function for the ghost
        void move_AI(double x, double y); //movement function
        void ai(); //AI function 
        void chase(Handle* u); //chasing function

};
#endif // GHOST_H
