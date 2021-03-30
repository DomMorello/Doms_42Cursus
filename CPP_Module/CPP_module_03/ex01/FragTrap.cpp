#include "./FragTrap.hpp"

FragTrap::FragTrap() : 
    hit(100), maxHit(100), energy(100),
    maxEnergy(100), level(1), name("unknown"), meleeDamage(30),
    rangedDamage(20), armorReduction(5) {
    std::cout << "Constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string name) :
    hit(100), maxHit(100), energy(100),
    maxEnergy(100), level(1), name(name), meleeDamage(30),
    rangedDamage(20), armorReduction(5) {
    std::cout << "Constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& fragTrap) {
    std::cout << "Copy constructor called" << std::endl;
    *this = fragTrap;   //대입연산자 오버로딩이 실행된다.
}

FragTrap::~FragTrap() {
    std::cout << "Destructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& fragTrap) {
    std::cout << "Assignation operator called" << std::endl;
    hit = fragTrap.hit;
    maxHit = fragTrap.maxHit;
    energy = fragTrap.energy;
    maxEnergy = fragTrap.maxEnergy;
    level = fragTrap.level;
    name = fragTrap.name;
    meleeDamage = fragTrap.meleeDamage;
    rangedDamage = fragTrap.rangedDamage;
    armorReduction = fragTrap.armorReduction;
    return *this;
}

unsigned int FragTrap::rangedAttack(std::string const & target) {
    std::cout <<
    "FR4G-TP "<< this->name << " attacks " << target <<
    " at range, causing " << this->rangedDamage << " points of damage!" << std::endl;
    return rangedDamage;
}

unsigned int FragTrap::meleeAttack(std::string const & target) {
    std::cout <<
    "FR4G-TP "<< this->name << " attacks " << target <<
    " at melee, causing " << this->meleeDamage << " points of damage!" << std::endl;
    return meleeDamage;
}

void FragTrap::takeDamage(unsigned int amount) {
    if (hit == 0)
    {
        std::cout << name << " is already dead" << std::endl;
        return ;
    }
    unsigned int damage = amount - armorReduction;
    if (damage < 0)
        damage = 0;
    std::cout <<
    "FR4G-TP "<< this->name << " is attacked and got "
    << damage << " points of damage!" << std::endl;
    hit -= damage;
    if (hit <= 0)
    {
        hit = 0;
        std::cout << name << " is dead" << std::endl;
        printStat();
    }
}

void FragTrap::beRepaired(unsigned int amount) {
    hit += amount;
    energy += amount;
    if (hit > maxHit)
        hit = maxHit;
    if (energy > maxEnergy)
        energy = maxEnergy;
    std::cout <<
    "FR4G-TP "<< this->name << " is repaired and got "
    << amount << " points of energy and hit points!" << std::endl;
}

unsigned int FragTrap::vaulthunter_dot_exe(std::string const & target) {
    //에너지가 25 미만이면 함수를 실행하지 않고 데미지 0을 리턴한다.
    if (energy < 25)
    {
        std::cout << "FAIL! out of energy" << std::endl;
        return 0;
    }
    energy -= 25;
    unsigned int randDamage[5] = {10, 20, 30, 40, 50};
    std::string randSkill[5] = {"punch", "kick", "stick", "flourescent light", "stone"};
    srand(clock());
    int random = rand() % 5;
        std::cout <<
    "FR4G-TP "<< this->name << " attacks " << target <<
    " at " << randSkill[random] << ", causing " << randDamage[random] << " points of damage!" << std::endl;
    return randDamage[random];
}

std::string FragTrap::getName() {
    return name;
}

void FragTrap::printStat() {
    std::cout << "==============================" << std::endl;
    std::cout << "name: " << this->name << std::endl;
    std::cout << "hit: " << this->hit << std::endl;
    std::cout << "energy: " << this->energy << std::endl;
    std::cout << "==============================" << std::endl;
}
