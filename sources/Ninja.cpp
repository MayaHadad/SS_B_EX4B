#include "Ninja.hpp"

namespace ariel
{
    Ninja::Ninja(int speed, Point location, int attackPoints, std::string name)
        : Character(location, attackPoints, name), _speed(speed)
    {
    }

    void Ninja::move(Character *enemy)
    {
        Point src = this->getLocation();
        Point dest = enemy->getLocation();
        Point point = Point::moveTowards(src, dest, this->_speed);
        this->setLocation(point);
    }

    void Ninja::slash(Character *enemy)
    {
        if (enemy == this || !this->isAlive() || !enemy->isAlive())
            throw std::runtime_error("can't shoot yourself\n");
        if (this->distance(enemy) <= 1)
            enemy->hit(40);
    }

    std::string Ninja::print()
    {
        std::cout << "N ";
        return this->Character::print();
    }
}