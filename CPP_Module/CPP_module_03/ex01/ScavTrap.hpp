#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include <iostream>
#include <string>
#include <ctime>

class ScavTrap {
    public:
        ScavTrap();
        ScavTrap(const std::string name);
        ScavTrap(const ScavTrap& scavTrap);
        ~ScavTrap();
        ScavTrap& operator=(const ScavTrap& scavTrap);
        int rangedAttack(std::string const & target);
        int meleeAttack(std::string const & target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        void challengeNewcomer(void);
        std::string getName();
        void printStat();

    private:
        int hit;    //hit가 maxHit보다 클 수 없다. 100
        int maxHit; //100
        int energy; //energy가 maxEnergy보다 클 수 없다. 50
        int maxEnergy;  //50
        int level;  //1
        std::string name;   
        int meleeDamage;   //20
        int rangedDamage;  //15
        int armorReduction; //3
};

#endif