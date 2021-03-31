#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "./ClapTrap.hpp"
#include <iostream>
#include <string>
#include <ctime>

class ScavTrap : public ClapTrap {
    public:
        ScavTrap();
        ScavTrap(const std::string name);
        ScavTrap(const ScavTrap& scavTrap);
        ~ScavTrap();
        ScavTrap& operator=(const ScavTrap& scavTrap);
        
        void challengeNewcomer(void);
};

#endif