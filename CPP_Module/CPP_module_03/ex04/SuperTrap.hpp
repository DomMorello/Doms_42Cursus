#ifndef SUPERTRAP_HPP
#define SUPERTRAP_HPP

#include "./FragTrap.hpp"
#include "./NinjaTrap.hpp"

class SuperTrap : public FragTrap, NinjaTrap {
    public:
        SuperTrap();
        SuperTrap(const std::string name);
        SuperTrap(const SuperTrap& scavTrap);
        ~SuperTrap();
        SuperTrap& operator=(const SuperTrap& scavTrap);
};

#endif