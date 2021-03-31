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
        void printStat(void);

        int hit;    //hit�� maxHit���� Ŭ �� ����. 100
        int maxHit; //100
        int energy; //energy�� maxEnergy���� Ŭ �� ����. 100
        int maxEnergy;  //100
        int level;  //1
        std::string name;   
        unsigned int meleeDamage;   //30
        unsigned int rangedDamage;  //20
        unsigned int armorReduction; //5
    private:
};

#endif