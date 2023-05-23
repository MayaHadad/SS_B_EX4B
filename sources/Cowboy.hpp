#pragma once

#include "Character.hpp"

namespace ariel
{
    class Cowboy : public Character
    {
        int bullets;

    public:
        Cowboy(std::string name, Point location);
        //~Cowboy();
        void shoot(Character *enemy);
        bool hasboolets();
        void reload();
        std::string print() override;
    };
}