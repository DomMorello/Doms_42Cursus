#include "./ClapTrap.hpp"

ClapTrap::ClapTrap() : 
    hit(0), maxHit(0), energy(0),
    maxEnergy(0), level(0), name("unknown"), meleeDamage(0),
    rangedDamage(0), armorReduction(0) {
    std::cout << "ClapTrap Constructor called lulu!" << std::endl;
}

ClapTrap::ClapTrap(const std::string name) :
    hit(0), maxHit(0), energy(0),
    maxEnergy(0), level(0), name(name), meleeDamage(0),
    rangedDamage(0), armorReduction(0) {
    std::cout << "ClapTrap Constructor called lulu!" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& clapTrap) {
    std::cout << "ClapTrap Copy constructor called lulu!" << std::endl;
    *this = clapTrap;   //���Կ����� �����ε��� ����ȴ�.
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap Destructor called lulu!" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& clapTrap) {
    std::cout << "ClapTrap Assignation operator called lulu!" << std::endl;
    hit = clapTrap.hit;
    maxHit = clapTrap.maxHit;
    energy = clapTrap.energy;
    maxEnergy = clapTrap.maxEnergy;
    level = clapTrap.level;
    name = clapTrap.name;
    meleeDamage = clapTrap.meleeDamage;
    rangedDamage = clapTrap.rangedDamage;
    armorReduction = clapTrap.armorReduction;
    return *this;
}

unsigned int ClapTrap::rangedAttack(std::string const & target) {
    std::cout <<
    this->name << " attacks " << target <<
    " at range, causing " << this->rangedDamage << " points of damage! shoot!" << std::endl;
    return rangedDamage;
}

unsigned int ClapTrap::meleeAttack(std::string const & target) {
    std::cout <<
    this->name << " attacks " << target <<
    " at melee, causing " << this->meleeDamage << " points of damage! shoot!" << std::endl;
    return meleeDamage;
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (hit == 0)
    {
        std::cout << name << " is already dead shoot!" << std::endl;
        return ;
    }
    unsigned int damage = amount - armorReduction;
    if (damage < 0)
        damage = 0;
    std::cout <<
    this->name << " is attacked and got "
    << damage << " points of damage! shoot!" << std::endl;
    hit -= damage;
    if (hit <= 0)
    {
        hit = 0;
        std::cout << this->name << " is dead shoot!" << std::endl;
        printStat();
    }
}

void ClapTrap::beRepaired(unsigned int amount) {
    hit += amount;
    energy += amount;
    if (hit > maxHit)
        hit = maxHit;
    if (energy > maxEnergy)
        energy = maxEnergy;
    std::cout <<
    this->name << " is repaired and got "
    << amount << " points of energy and hit points! shoot!" << std::endl;
}

std::string ClapTrap::getName(void) {
    return name;
}

void ClapTrap::printStat(void) {
    std::cout << "==============================" << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "hit: " << hit << std::endl;
    std::cout << "energy: " << energy << std::endl;
    std::cout << "==============================" << std::endl;
}
