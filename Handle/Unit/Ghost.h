#ifndef GHOST_H
#define GHOST_H

#include "Unit.h"

class Ghost : public Unit {
    private:
        Unit *chasing_target;


        // given a coordinate, randomly pick a coordinate within a radius centered at patrolCenter
        // once reach that random coordinate, pick another coordinate and move to that point
        // if survivor get into visible range, chase that unit
        // if the ghost leave the chasingRadius centered at patrolCenter, back to patrolCenter
        // before arrived patrolCenter, ghost will no longer chase a unit
        double patrolCenterLocation[2]; // coordinate of center
        double randomTargetLocation[2];
    public:
        explicit Ghost(Map *map, double x, double y, Unit *chasing_target = nullptr);
        static const int base_max_health = 5;
        static const float base_collison_radius;
        static const double base_max_speed;

        static const int base_damage = 1;
        static const float base_attackInterval;
        static const float base_attack_radius;
        static const double base_attack_sector_angle;
        static const int base_armor = 1;
        static const int base_visible_radius = 80;

        static const double patrolRadius;
        static const double chasingRadius;


        // void attack();
        void patrol();
        void move_AI(double x, double y);
        void chase(Unit* u);

};
#endif // GHOST_H
