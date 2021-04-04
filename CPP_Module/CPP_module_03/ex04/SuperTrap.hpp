#ifndef SUPERTRAP_HPP
#define SUPERTRAP_HPP

#include "./NinjaTrap.hpp"

class SuperTrap : public FragTrap, public NinjaTrap {
    public:
        SuperTrap();
        SuperTrap(const std::string name);
        SuperTrap(const SuperTrap& superTrap);
        ~SuperTrap();
        SuperTrap& operator=(const SuperTrap& superTrap);

        unsigned int rangedAttack(std::string const & target);
        unsigned int meleeAttack(std::string const & target);
};

#endif