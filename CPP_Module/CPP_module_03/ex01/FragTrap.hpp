#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include <iostream>
#include <string>
#include <ctime>

class FragTrap {
    public:
        FragTrap();
        FragTrap(const std::string name);
        FragTrap(const FragTrap& fragTrap);
        ~FragTrap();
        FragTrap& operator=(const FragTrap& fragTrap);
        unsigned int rangedAttack(std::string const & target);
        unsigned int meleeAttack(std::string const & target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        unsigned int vaulthunter_dot_exe(std::string const & target);
        std::string getName();
        void printStat();

    private:
        int hit;    //hit�� maxHit���� Ŭ �� ����. 100
        int maxHit; //100
        int energy; //energy�� maxEnergy���� Ŭ �� ����. 100
        int maxEnergy;  //100
        int level;  //1
        std::string name;   
        unsigned int meleeDamage;   //30
        unsigned int rangedDamage;  //20
        unsigned int armorReduction; //5
};

#endif