#include "./SuperTrap.hpp"

SuperTrap::SuperTrap() : ClapTrap(), FragTrap(), NinjaTrap()
{
    name = "unknown";
    hit = 100;
    maxHit = 100;
    energy = 120;
    maxEnergy = 120;
    level = 1;
    meleeDamage = 60;
    rangedDamage = 20;
    armorReduction = 5;
	std::cout << "SuperTrap Constructor called ulala!" << std::endl; 
}

SuperTrap::SuperTrap(std::string name): ClapTrap(name), FragTrap(name), NinjaTrap(name)
{
    this->name = name;
    hit = 100;
    maxHit = 100;
    energy = 120;
    maxEnergy = 120;
    level = 1;
    meleeDamage = 60;
    rangedDamage = 20;
    armorReduction = 5;
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

unsigned int SuperTrap::rangedAttack(std::string const & target) {
    return FragTrap::rangedAttack(target);
}

unsigned int SuperTrap::meleeAttack(std::string const & target) {
    return NinjaTrap::meleeAttack(target);
}