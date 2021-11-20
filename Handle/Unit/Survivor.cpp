#include "Survivor.h"
#include <chrono>
const float Survivor::base_collison_radius = 16.0;
const double Survivor::base_max_speed = 20.0;
const float Survivor::base_attackInterval = 1.0;
const float Survivor::base_attack_radius = 16.0;

Survivor::Survivor(Map* map, double x, double y) : Unit(map, x, y) {
    pathable += Map::Terrain::GRASS;
    pathable += Map::Terrain::STONE;
    pathable += Map::Terrain::SHOAL;
}

void Survivor::attack() {
    //set attack interval of survivor

     auto t_start = std::chrono::high_resolution_clock::now();
    /*get all Handle that within radius (60 degree of the circle(radius = attack_radius, center = Coordinate(Survivor)) in front of Survivor)
    if :
        1. Handle is not invulnerable
        2. Handle is Unit
        3. attack(Survivor) > armor(Unit)
    then
    deal (attack(Survivor) - armor(Unit)) amount of attack to Unit

    */
    while (true)
    {
    auto t_end = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<float, milli>(t_end - t_start).count() > 1 / base_attackInterval)
    {
        //cout << chrono::duration<float, milli>(t_end - t_start).count() << endl;
        break;
    }
    }
}