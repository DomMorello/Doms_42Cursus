#include "./ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
    name = "unknown";
    hit = 100;
    maxHit = 100;
    energy = 50;
    maxEnergy = 50;
    level = 1;
    meleeDamage = 20;
    rangedDamage = 15;
    armorReduction = 3;
	std::cout << "ScavTrap Constructor called yeah!" << std::endl; 
}

ScavTrap::ScavTrap(std::string name): ClapTrap(name)
{
    this->name = name;
    hit = 100;
    maxHit = 100;
    energy = 50;
    maxEnergy = 50;
    level = 1;
    meleeDamage = 20;
    rangedDamage = 15;
    armorReduction = 3;
	std::cout << "ScavTrap Constructor called yeah!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& scavTrap) {
    std::cout << "ScavTrap Copy constructor called yeah!" << std::endl;
    *this = scavTrap;   //���Կ����� �����ε��� ����ȴ�.
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap Destructor called yeah!" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& scavTrap) {
    std::cout << "ScavTrap Assignation operator called yeah!" << std::endl;
    this->hit = scavTrap.hit;
    this->maxHit = scavTrap.maxHit;
    this->energy = scavTrap.energy;
    this->maxEnergy = scavTrap.maxEnergy;
    this->level = scavTrap.level;
    this->name = scavTrap.name;
    this->meleeDamage = scavTrap.meleeDamage;
    this->rangedDamage = scavTrap.rangedDamage;
    this->armorReduction = scavTrap.armorReduction;
    return *this;
}

void ScavTrap::challengeNewcomer(void) {
    const std::string randChallenges[5] = {
        "Drop the Hammer",
        "I Am Rubber, You Are Glue",
        "Start With a Bang",
        "Hyperion Punch",
        "One Last Thing"
    };
    srand(clock());
    std::cout << "Scavtrap says: " << randChallenges[rand() % 5] << std::endl;
}