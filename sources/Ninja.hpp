#pragma once

#include "Character.hpp"

namespace ariel
{
    class Ninja : public Character
    {
        int _speed;

        public:
            Ninja(int speed, Point location, int attackPoints, std::string name);
            // ~Ninja();
            void move(Character *enemy);
            void slash(Character *enemy);
            std::string print() override;
    };
}