#include "./SuperTrap.hpp"

SuperTrap::SuperTrap() : FragTrap(), NinjaTrap()
{
    name = "unknown";
    hit = FragTrap::hit;
    maxHit = FragTrap::maxHit;
    energy = NinjaTrap::energy;
    maxEnergy = NinjaTrap::maxEnergy;
    level = 1;
    meleeDamage = NinjaTrap::meleeDamage;
    rangedDamage = FragTrap::rangedDamage;
    armorReduction = FragTrap::armorReduction;
	std::cout << "SuperTrap Constructor called ulala!" << std::endl; 
}

SuperTrap::SuperTrap(std::string name): FragTrap(name), NinjaTrap(name)
{
    this->name = name;
    hit = FragTrap::hit;
    maxHit = FragTrap::maxHit;
    energy = NinjaTrap::energy;
    maxEnergy = NinjaTrap::maxEnergy;
    level = 1;
    meleeDamage = NinjaTrap::meleeDamage;
    rangedDamage = FragTrap::rangedDamage;
    armorReduction = FragTrap::armorReduction;
	std::cout << "SuperTrap Constructor called ulala!" << std::endl;
}

SuperTrap::SuperTrap(const SuperTrap& superTrap) {
    std::cout << "SuperTrap Copy constructor called ulala!" << std::endl;
    *this = superTrap;   //���Կ����� �����ε��� ����ȴ�.
}

SuperTrap::~SuperTrap() {
    std::cout << "SuperTrap Destructor called ulala!" << std::endl;
}

SuperTrap& SuperTrap::operator=(const SuperTrap& superTrap) {
    std::cout << "SuperTrap Assignation operator called ulala!" << std::endl;
    this->hit = superTrap.hit;
    this->maxHit = superTrap.maxHit;
    this->energy = superTrap.energy;
    this->maxEnergy = superTrap.maxEnergy;
    this->level = superTrap.level;
    this->name = superTrap.name;
    this->meleeDamage = superTrap.meleeDamage;
    this->rangedDamage = superTrap.rangedDamage;
    this->armorReduction = superTrap.armorReduction;
    return *this;
}