#include "SmartTeam.hpp"

namespace ariel
{
    SmartTeam::SmartTeam(Character *leader) : Team(leader)
    {
        if (leader == nullptr)
            throw std::runtime_error("invalid leader for team2");
    }

    void SmartTeam::add(Character *character)
    {
        if (character == nullptr || !character->isAlive() || this->getTeam().size() == 10 || character->getPlaying() == 1)
            throw std::runtime_error("can't add player to team\n");

        if (dynamic_cast<Cowboy *>(character) != nullptr)
            this->getTeam().push_back(character);

        else if (dynamic_cast<Ninja *>(character) != nullptr)
        {
            size_t index = 0;
            for (size_t i = 0; i < this->getTeam().size(); i++)
            {
                if (dynamic_cast<Ninja *>(this->getTeam().at(i)) != nullptr)
                    index++;
            }
            if (index == this->getTeam().size()) // only ninjas in vector
                this->getTeam().push_back(character);
            else
            {
                // shift cowboys
                this->getTeam().push_back(nullptr);
                for (size_t i = this->getTeam().size() - 1; i > index; i--)
                    this->getTeam().at(i) = this->getTeam().at(i - 1);
                // add ninja
                this->getTeam().at(index) = character;
            }
        }
        character->setPlaying(1);
    }

    /* ninjas attack first.
     each ninja attacks an enemy that is closest to it.
     then the cowboys attack the enemy teammate with the least amount of points.*/
    void SmartTeam::attack(Team *enemy)
    {
        if (enemy == nullptr)
            throw std::invalid_argument("can't attack\n");
        else if (enemy == this || enemy->getTeam().size() == 0 || this->getTeam().size() == 0 ||
                 enemy->stillAlive() == 0 || this->stillAlive() == 0)
            throw std::runtime_error("can't attack\n");

        for (size_t i = 0; i < this->getTeam().size(); i++)
        {
            size_t player_to_attack=0;
            Cowboy *cowboy = dynamic_cast<Cowboy *>(this->getTeam().at(i));
            Ninja *ninja = dynamic_cast<Ninja *>(this->getTeam().at(i));
            if (cowboy != nullptr && cowboy->isAlive())
            {
                // player is a cowboy
                player_to_attack = choose_victim_by_health(enemy);
                if(player_to_attack == 10)
                    return;
                if (!cowboy->hasboolets())
                    cowboy->reload();
                cowboy->shoot(enemy->getTeam().at(player_to_attack));
            }
            else if (ninja != nullptr && ninja->isAlive())
            {
                // player is a cowboy
                player_to_attack = choose_victim_by_distance(ninja, enemy);
                if(player_to_attack == 10)
                    return;
                if (ninja->distance(enemy->getTeam().at(player_to_attack)) > 1)
                    ninja->move(enemy->getTeam().at(player_to_attack));
                ninja->slash(enemy->getTeam().at(player_to_attack));
            }
        }
    }

    size_t SmartTeam::choose_victim_by_health(Team *team)
    {
        if (team == nullptr || team->stillAlive() == 0)
            throw("invalid team");
        int minhealth = __INT_MAX__;
        size_t index;
        for (size_t i = 0; i < team->getTeam().size(); i++)
        {
            int health = team->getTeam().at(i)->getAttackPoints();
            if (health < minhealth)
            {
                minhealth = health;
                index = i;
            }
        }
        return index;
    }
}