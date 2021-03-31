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
        void printStat(void);

        int hit;    //hit�� maxHit���� Ŭ �� ����. 100
        int maxHit; //100
        int energy; //energy�� maxEnergy���� Ŭ �� ����. 50
        int maxEnergy;  //50
        int level;  //1
        std::string name;   
        int meleeDamage;   //20
        int rangedDamage;  //15
        int armorReduction; //3
    private:
};

#endif