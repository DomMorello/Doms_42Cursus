#include "./NinjaTrap.hpp"

NinjaTrap::NinjaTrap() : ClapTrap()
{
    name = "unknown";
    hit = 60;
    maxHit = 60;
    energy = 120;
    maxEnergy = 120;
    level = 1;
    meleeDamage = 60;
    rangedDamage = 5;
    armorReduction = 0;
	std::cout << "NinjaTrap Constructor called wow!" << std::endl; 
}

NinjaTrap::NinjaTrap(std::string name): ClapTrap(name)
{
    this->name = name;
    hit = 60;
    maxHit = 60;
    energy = 120;
    maxEnergy = 120;
    level = 1;
    meleeDamage = 60;
    rangedDamage = 5;
    armorReduction = 0;
	std::cout << "NinjaTrap Constructor called wow!" << std::endl;
}

NinjaTrap::NinjaTrap(const NinjaTrap& ninjaTrap) {
    std::cout << "NinjaTrap Copy constructor called wow!" << std::endl;
    *this = ninjaTrap;   //���Կ����� �����ε��� ����ȴ�.
}

NinjaTrap::~NinjaTrap() {
    std::cout << "NinjaTrap Destructor called wow!" << std::endl;
}

NinjaTrap& NinjaTrap::operator=(const NinjaTrap& ninjaTrap) {
    std::cout << "NinjaTrap Assignation operator called wow!" << std::endl;
    this->hit = ninjaTrap.hit;
    this->maxHit = ninjaTrap.maxHit;
    this->energy = ninjaTrap.energy;
    this->maxEnergy = ninjaTrap.maxEnergy;
    this->level = ninjaTrap.level;
    this->name = ninjaTrap.name;
    this->meleeDamage = ninjaTrap.meleeDamage;
    this->rangedDamage = ninjaTrap.rangedDamage;
    this->armorReduction = ninjaTrap.armorReduction;
    return *this;
}
void NinjaTrap::ninjaShoebox(ClapTrap& clapTrap) {
    if (energy < 25)
    {
        std::cout << "FAIL! out of energy holy!" << std::endl;
        return ;
    }
    energy -= 25;
    std::cout << this->name << " attacks ClapTrap:"
    << clapTrap.getName() << " very swiftly!" << std::endl;
}

void NinjaTrap::ninjaShoebox(FragTrap& fragTrap) {
    if (energy < 25)
    {
        std::cout << "FAIL! out of energy holy!" << std::endl;
        return ;
    }
    energy -= 25;
    std::cout << this->name << " attacks FragTrap:"
    << fragTrap.getName() << " very swiftly!" << std::endl;
}

void NinjaTrap::ninjaShoebox(ScavTrap& scavTrap) {
    if (energy < 25)
    {
        std::cout << "FAIL! out of energy holy!" << std::endl;
        return ;
    }
    energy -= 25;
    std::cout << this->name << " attacks ScavTrap:"
    << scavTrap.getName() << " very swiftly!" << std::endl;
}

void NinjaTrap::ninjaShoebox(NinjaTrap& ninjaTrap) {
    if (energy < 25)
    {
        std::cout << "FAIL! out of energy holy!" << std::endl;
        return ;
    }
    std::cout << this->name << " attacks NinjaTrap:"
    << ninjaTrap.getName() << " very swiftly!" << std::endl;
}
