#pragma once

#include <iostream>
#include <vector>
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"

namespace ariel
{
    class Team
    {
        size_t leader_index;
        std::vector<Character *> team;

    public:
        Team(Character *leader);
        Team(const Team &other);
        Team &operator=(const Team &other);
        Team(Team &&other) noexcept;
        Team &operator=(Team &&other) noexcept;
        virtual ~Team();
        virtual void add(Character *character);
        virtual void attack(Team *enemy);
        int stillAlive();
        void print();
        std::vector<Character *> &getTeam();
        size_t choose_victim_by_distance(Character *character, Team *enemy);
    };
}