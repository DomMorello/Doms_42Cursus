#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap {
    public:
        ClapTrap();
        ClapTrap(const std::string name);
        ClapTrap(const ClapTrap& clapTrap);
        virtual ~ClapTrap();
        ClapTrap& operator=(const ClapTrap& clapTrap);
        
        unsigned int rangedAttack(std::string const & target);
        unsigned int meleeAttack(std::string const & target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        std::string getName(void);
        void printStat(void);

        int hit;
        int maxHit;
        int energy;
        int maxEnergy;
        int level;
        std::string name;
        unsigned int meleeDamage;
        unsigned int rangedDamage;
        unsigned int armorReduction;
    private:
};

#endif