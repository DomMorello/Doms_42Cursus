#include "./ScavTrap.hpp"

ScavTrap::ScavTrap() : 
    ClapTrap(),
    hit(100), maxHit(100), energy(50),
    maxEnergy(50), level(1), name("unknown"), meleeDamage(20),
    rangedDamage(15), armorReduction(3) {
    std::cout << "ScavTrap Constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string name) :
    ClapTrap(name),
    hit(100), maxHit(100), energy(50),
    maxEnergy(50), level(1), name(name), meleeDamage(20),
    rangedDamage(15), armorReduction(3) {
    std::cout << "ScavTrap Constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& scavTrap) {
    std::cout << "ScavTrap Copy constructor called" << std::endl;
    *this = scavTrap;   //���Կ����� �����ε��� ����ȴ�.
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap Destructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& scavTrap) {
    std::cout << "ScavTrap Assignation operator called" << std::endl;
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

void ScavTrap::printStat(void) {
    std::cout << "==============================" << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "hit: " << hit << std::endl;
    std::cout << "energy: " << energy << std::endl;
    std::cout << "==============================" << std::endl;
}