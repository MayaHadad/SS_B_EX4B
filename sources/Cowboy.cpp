#include "Cowboy.hpp"

namespace ariel
{
    Cowboy::Cowboy(std::string name, Point location) : Character(location, 110, name), bullets(6)
    {
    }

    void Cowboy::shoot(Character *enemy)
    {
        if (!enemy->isAlive() || enemy == this || !this->isAlive())
            throw std::runtime_error("can't shoot\n");
        if (this->hasboolets() && enemy->isAlive())
        {
            enemy->hit(10);
            bullets -= 1;
        }
    }

    bool Cowboy::hasboolets()
    {
        if (bullets > 0)
            return true;
        return false;
    }

    void Cowboy::reload()
    {
        if (!this->isAlive())
            throw std::runtime_error("can't reload\n");
        bullets = 6;
    }

    std::string Cowboy::print()
    {
        std::cout << "C ";
        return this->Character::print();
    }
}