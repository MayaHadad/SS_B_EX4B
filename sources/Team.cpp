#include "Team.hpp"

using namespace std;

namespace ariel
{
    Team::Team(Character *leader) : leader_index(0)
    {
        if (leader == NULL || leader->getPlaying() == 1)
            throw std::runtime_error("invalid leader for team");
        team.push_back(leader);
        leader->setPlaying(1);
    }

    Team::~Team()
    {
        for (size_t i = 0; i < team.size(); i++)
            delete team.at(i);
    }

    void Team::add(Character *character)
    {
        if (character == NULL || !character->isAlive() || team.size() == 10 || character->getPlaying() == 1)
            throw std::runtime_error("can't add player to team\n");

        if (dynamic_cast<Ninja *>(character) != nullptr)
            team.push_back(character);

        else if (dynamic_cast<Cowboy *>(character) != nullptr)
        {
            size_t index = 0;
            for (size_t i = 0; i < team.size(); i++)
            {
                if (dynamic_cast<Cowboy *>(team.at(i)) != nullptr)
                    index++;
            }
            if (index == team.size()) // only cowboys in vector
                team.push_back(character);
            else
            {
                // shift ninjas
                team.push_back(nullptr);
                for (size_t i = team.size() - 1; i > index; i--)
                    team.at(i) = team.at(i - 1);
                // add cowboy
                team.at(index) = character;
                // shift index of leader
                if (leader_index >= index)
                    leader_index += 1;
            }
        }
        character->setPlaying(1);
    }

    void Team::attack(Team *enemy)
    {
        if (enemy == nullptr)
            throw std::invalid_argument("can't attack\n");
        else if (enemy == this || enemy->team.size() == 0 || this->team.size() == 0 ||
                 enemy->stillAlive() == 0 || this->stillAlive() == 0)
            throw std::runtime_error("can't attack\n");

        // check if leader is alive. if not get new leader
        if (!team.at(leader_index)->isAlive())
        {
            int mindist = __INT_MAX__;
            size_t new_leader_index;
            for (size_t i = 0; i < team.size(); i++)
            {
                int dist = team.at(leader_index)->distance(team.at(i));
                if (dist < mindist && team.at(i)->isAlive())
                {
                    mindist = dist;
                    new_leader_index = i;
                }
            }
            leader_index = new_leader_index;
        }

        // choosing victom. can't be 10 because enemy->stillAlive() != 0
        size_t index_of_victim = this->choose_victim_by_distance(team.at(leader_index), enemy);

        // attack
        size_t i = 0;
        while (i < team.size())
        {
            if (index_of_victim == 10)
                break;

            if (team.at(i)->isAlive())
            {
                Cowboy *cowboy = dynamic_cast<Cowboy *>(team.at(i));
                Ninja *ninja = dynamic_cast<Ninja *>(team.at(i));
                if (cowboy != nullptr)
                {
                    if (cowboy->hasboolets())
                        cowboy->shoot(enemy->team.at(index_of_victim));
                    else
                        cowboy->reload();
                }
                else if (ninja != nullptr)
                {
                    ninja->slash(enemy->team.at(index_of_victim));
                    if (ninja->distance(enemy->team.at(index_of_victim)) > 1)
                        ninja->move(enemy->team.at(index_of_victim));
                }
            }
            i++;

            if (!enemy->team.at(index_of_victim)->isAlive())
                index_of_victim = this->choose_victim_by_distance(team.at(leader_index), enemy);
        }
    }

    int Team::stillAlive()
    {
        int alive = 0;
        for (size_t i = 0; i < team.size(); i++)
        {
            if (team.at(i)->isAlive())
                alive++;
        }
        return alive;
    }

    void Team::print()
    {
        for (size_t i = 0; i < team.size(); i++)
        {
            Cowboy *cowboy = dynamic_cast<Cowboy *>(team.at(i));
            Ninja *ninja = dynamic_cast<Ninja *>(team.at(i));
            if (cowboy != nullptr)
                cowboy->print();
            else if (ninja != nullptr)
                ninja->print();
        }
    }

    size_t Team::choose_victim_by_distance(Character *character, Team *enemy)
    {
        if (enemy->stillAlive() == 0)
            return 10;
        size_t index_of_victim = 0;
        int mindist = __INT_MAX__;
        for (size_t i = 0; i < enemy->team.size(); i++)
        {
            int dist = character->distance(enemy->team.at(i));
            if (dist < mindist && enemy->team.at(i)->isAlive())
            {
                mindist = dist;
                index_of_victim = i;
            }
        }
        return index_of_victim;
    }

    std::vector<Character *> &Team::getTeam()
    {
        return team;
    }
}