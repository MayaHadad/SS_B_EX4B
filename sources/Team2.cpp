#include "Team2.hpp"

namespace ariel
{
    Team2::Team2(Character *leader) : Team(leader)
    {
        if (leader == NULL)
            throw std::runtime_error("invalid leader for team2");
    }

    void Team2::add(Character *character)
    {
        if(character == NULL || !character->isAlive() || this->getTeam().size() == 10 || character->getPlaying()==1)
            throw std::runtime_error("can't add player");

        this->getTeam().push_back(character);
        character->setPlaying(1);
    }

    void Team2::attack(Team *enemy){
        this->Team::attack(enemy);
    }
}