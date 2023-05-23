#pragma once

#include "Team.hpp"

namespace ariel{
    class SmartTeam : public Team
    {
        size_t choose_victim_by_health(Team *team);

        public:
            SmartTeam(Character *leader);
            void add(Character *character) override;
            void attack(Team *enemy) override;
    };
}