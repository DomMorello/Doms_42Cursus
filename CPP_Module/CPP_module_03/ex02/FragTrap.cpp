#include "./FragTrap.hpp"

FragTrap::FragTrap() :
    ClapTrap(),
    hit(100), maxHit(100), energy(100),
    maxEnergy(100), level(1), name("unknown"), meleeDamage(30),
    rangedDamage(20), armorReduction(5) {
    std::cout << "FragTrap Constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string name) :
    ClapTrap(name),
    hit(100), maxHit(100), energy(100),
    maxEnergy(100), level(1), name(name), meleeDamage(30),
    rangedDamage(20), armorReduction(5) {
    std::cout << "FragTrap Constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& fragTrap) {
    std::cout << "FragTrap Copy constructor called" << std::endl;
    *this = fragTrap;   //���Կ����� �����ε��� ����ȴ�.
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap Destructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& fragTrap) {
    std::cout << "FragTrap Assignation operator called" << std::endl;
    this->hit = fragTrap.hit;
    this->maxHit = fragTrap.maxHit;
    this->energy = fragTrap.energy;
    this->maxEnergy = fragTrap.maxEnergy;
    this->level = fragTrap.level;
    this->name = fragTrap.name;
    this->meleeDamage = fragTrap.meleeDamage;
    this->rangedDamage = fragTrap.rangedDamage;
    this->armorReduction = fragTrap.armorReduction;
    return *this;
}

unsigned int FragTrap::vaulthunter_dot_exe(std::string const & target) {
    //�������� 25 �̸��̸� �Լ��� �������� �ʰ� ������ 0�� �����Ѵ�.
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

void FragTrap::printStat(void) {
    std::cout << "==============================" << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "hit: " << hit << std::endl;
    std::cout << "energy: " << energy << std::endl;
    std::cout << "==============================" << std::endl;
}