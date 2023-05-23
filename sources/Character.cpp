#include "Character.hpp"

namespace ariel
{
    Character::Character(Point location, int attackPoints, std::string name)
        : _location(location.getX(), location.getY()), _attackPoints(attackPoints), _name(name), playing(0)
    {
    }

    bool Character::isAlive()
    {
        if (_attackPoints > 0)
            return true;
        return false;
    }

    double Character::distance(Character *other)
    {
        return this->_location.distance(other->_location);
    }

    void Character::hit(int harmPoints)
    {
        if (harmPoints < 0)
            throw std::invalid_argument("harm point are negative\n");
        if (harmPoints > 0)
            _attackPoints -= harmPoints;
    }

    std::string Character::getName()
    {
        return _name;
    }

    Point Character::getLocation()
    {
        return _location;
    }

    std::string Character::print()
    {
        std::cout << "name: " << this->_name << ", attack points: " << this->_attackPoints << ", location: ";
        this->_location.print();

        return "";
    }

    int Character::getAttackPoints()
    {
        return _attackPoints;
    }

    void Character::setAttackPoint(int num)
    {
        this->_attackPoints = num;
    }

    void Character::setLocation(Point &point)
    {
        this->_location.setX(point.getX());
        this->_location.setY(point.getY());
    }

    int Character::getPlaying()
    {
        return playing;
    }

    void Character::setPlaying(int playing)
    {
        this->playing = playing;
    }

}