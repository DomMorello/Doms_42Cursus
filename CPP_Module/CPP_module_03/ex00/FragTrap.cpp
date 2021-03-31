#include "./FragTrap.hpp"

FragTrap::FragTrap() : 
    hit(100), maxHit(100), energy(100),
    maxEnergy(100), level(1), name("unknown"), meleeDamage(30),
    rangedDamage(20), armorReduction(5) {
    std::cout << "Constructor called yoohoo" << std::endl;
}

FragTrap::FragTrap(const std::string name) :
    hit(100), maxHit(100), energy(100),
    maxEnergy(100), level(1), name(name), meleeDamage(30),
    rangedDamage(20), armorReduction(5) {
    std::cout << "Constructor called yoohoo" << std::endl;
}

FragTrap::FragTrap(const FragTrap& fragTrap) {
    std::cout << "Copy constructor called yoohoo" << std::endl;
    *this = fragTrap;   //���Կ����� �����ε��� ����ȴ�.
}

FragTrap::~FragTrap() {
    std::cout << "Destructor called yoohoo" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& fragTrap) {
    std::cout << "Assignation operator called yoohoo" << std::endl;
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
    " at range, causing " << this->rangedDamage << " points of damage! holy!" << std::endl;
    return rangedDamage;
}

unsigned int FragTrap::meleeAttack(std::string const & target) {
    std::cout <<
    "FR4G-TP "<< this->name << " attacks " << target <<
    " at melee, causing " << this->meleeDamage << " points of damage! holy!" << std::endl;
    return meleeDamage;
}

void FragTrap::takeDamage(unsigned int amount) {
    if (hit == 0)
    {
        std::cout << name << " is already dead holy!" << std::endl;
        return ;
    }
    unsigned int damage = amount - armorReduction;
    if (damage < 0)
        damage = 0;
    std::cout <<
    "FR4G-TP "<< this->name << " is attacked and got "
    << damage << " points of damage! holy!" << std::endl;
    hit -= damage;
    if (hit <= 0)
    {
        hit = 0;
        std::cout << name << " is dead holy!" << std::endl;
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
    << amount << " points of energy and hit points! holy!" << std::endl;
}

unsigned int FragTrap::vaulthunter_dot_exe(std::string const & target) {
    //�������� 25 �̸��̸� �Լ��� �������� �ʰ� ������ 0�� �����Ѵ�.
    if (energy < 25)
    {
        std::cout << "FAIL! out of energy holy!" << std::endl;
        return 0;
    }
    energy -= 25;
    unsigned int randDamage[5] = {10, 20, 30, 40, 50};
    const std::string randSkill[5] = {"punch", "kick", "stick", "flourescent light", "stone"};
    srand(clock());
    int random = rand() % 5;
        std::cout <<
    "FR4G-TP "<< this->name << " attacks " << target <<
    " at " << randSkill[random] << ", causing " << randDamage[random] << " points of damage! holy!" << std::endl;
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
