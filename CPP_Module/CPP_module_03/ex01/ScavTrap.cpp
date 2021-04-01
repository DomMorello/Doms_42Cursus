#include "./ScavTrap.hpp"

ScavTrap::ScavTrap() : 
    hit(100), maxHit(100), energy(50),
    maxEnergy(50), level(1), name("unknown"), meleeDamage(20),
    rangedDamage(15), armorReduction(3) {
    std::cout << "ScavTrap Constructor called wow!" << std::endl;
}

ScavTrap::ScavTrap(const std::string name) :
    hit(100), maxHit(100), energy(50),
    maxEnergy(50), level(1), name(name), meleeDamage(20),
    rangedDamage(15), armorReduction(3) {
    std::cout << "ScavTrap Constructor called wow!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& scavTrap) {
    std::cout << "ScavTrap Copy constructor called wow!" << std::endl;
    *this = scavTrap;   //���Կ����� �����ε��� ����ȴ�.
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap Destructor called wow!" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& scavTrap) {
    std::cout << "ScavTrap Assignation operator called wow!" << std::endl;
    hit = scavTrap.hit;
    maxHit = scavTrap.maxHit;
    energy = scavTrap.energy;
    maxEnergy = scavTrap.maxEnergy;
    level = scavTrap.level;
    name = scavTrap.name;
    meleeDamage = scavTrap.meleeDamage;
    rangedDamage = scavTrap.rangedDamage;
    armorReduction = scavTrap.armorReduction;
    return *this;
}

int ScavTrap::rangedAttack(std::string const & target) {
    std::cout <<
    "FR4G-TP(scavtrap) "<< this->name << " attacks " << target <<
    " at range, causing " << this->rangedDamage << " points of damage! yeah!" << std::endl;
    return rangedDamage;
}

int ScavTrap::meleeAttack(std::string const & target) {
    std::cout <<
    "FR4G-TP(scavtrap) "<< this->name << " attacks " << target <<
    " at melee, causing " << this->meleeDamage << " points of damage! yeah!" << std::endl;
    return meleeDamage;
}

void ScavTrap::takeDamage(unsigned int amount) {
    if (hit == 0)
    {
        std::cout << name << " is already dead yeah!" << std::endl;
        return ;
    }
    int damage = amount - armorReduction;
    if (damage < 0)
        damage = 0;
    std::cout <<
    "FR4G-TP(scavtrap) "<< this->name << " is attacked and got "
    << damage << " points of damage! yeah!" << std::endl;
    hit -= damage;
    if (hit <= 0)
    {
        hit = 0;
        std::cout << name << " is dead yeah!" << std::endl;
        printStat();
    }
}

void ScavTrap::beRepaired(unsigned int amount) {
    hit += amount;
    energy += amount;
    if (hit > maxHit)
        hit = maxHit;
    if (energy > maxEnergy)
        energy = maxEnergy;
    std::cout <<
    "FR4G-TP(scavtrap) "<< this->name << " is repaired and got "
    << amount << " points of energy and hit points! yeah!" << std::endl;
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

std::string ScavTrap::getName() {
    return name;
}

void ScavTrap::printStat() {
    std::cout << "==============================" << std::endl;
    std::cout << "name: " << this->name << std::endl;
    std::cout << "hit: " << this->hit << std::endl;
    std::cout << "energy: " << this->energy << std::endl;
    std::cout << "==============================" << std::endl;
}