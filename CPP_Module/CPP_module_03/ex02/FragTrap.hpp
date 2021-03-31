#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "./ClapTrap.hpp"
#include <iostream>
#include <string>
#include <ctime>

class FragTrap : public ClapTrap {
    public:
        FragTrap();
        FragTrap(const std::string name);
        FragTrap(const FragTrap& fragTrap);
        ~FragTrap();
        FragTrap& operator=(const FragTrap& fragTrap);

        unsigned int vaulthunter_dot_exe(std::string const & target);
};

#endif