#ifndef NINJATRAP_HPP
#define NINJATRAP_HPP

#include "./ClapTrap.hpp"
#include "./FragTrap.hpp"
#include "./ScavTrap.hpp"

class NinjaTrap : virtual public ClapTrap {
    public:
        NinjaTrap();
        NinjaTrap(const std::string name);
        NinjaTrap(const NinjaTrap& ninjaTrap);
        ~NinjaTrap();
        NinjaTrap& operator=(const NinjaTrap& ninjaTrap);

        void ninjaShoebox(ClapTrap& clapTrap);
        void ninjaShoebox(FragTrap& fragTrap);
        void ninjaShoebox(ScavTrap& scavTrap);
        void ninjaShoebox(NinjaTrap& ninjaTrap);
};

#endif