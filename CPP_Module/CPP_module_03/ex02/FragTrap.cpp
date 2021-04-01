#include "./FragTrap.hpp"

//이 부분을 처음에는 리스트 초기화 방법으로 했는데 그 방법은
//해당 클래스 내부에 존재하는 맴버변수만 그런 식으로 가능하다.
//부모 클래스에 protected로 접근자를 설정한 맴버변수에 대해서
//자식 클래스에서 접근이 가능하지만 리스트 초기화 방법으로는 접근이 불가능하다.
//이 부분에서 많은 시간을 보냈다.
FragTrap::FragTrap() : ClapTrap()
{
    name = "unknown";
    hit = 100;
    maxHit = 100;
    energy = 100;
    maxEnergy = 100;
    level = 1;
    meleeDamage = 30;
    rangedDamage = 20;
    armorReduction = 5;
	std::cout << "FragTrap Constructor called yoo hoo!" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
    this->name = name;
    hit = 100;
    maxHit = 100;
    energy = 100;
    maxEnergy = 100;
    level = 1;
    meleeDamage = 30;
    rangedDamage = 20;
    armorReduction = 5;
	std::cout << "FragTrap Constructor called yoo hoo!" << std::endl;
}

FragTrap::FragTrap(const FragTrap& fragTrap) {
    std::cout << "FragTrap Copy constructor called yoo hoo!" << std::endl;
    *this = fragTrap;   //���Կ����� �����ε��� ����ȴ�.
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap Destructor called yoo hoo!" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& fragTrap) {
    std::cout << "FragTrap Assignation operator called yoo hoo!" << std::endl;
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
        std::cout << "FAIL! out of energy holy!" << std::endl;
        return 0;
    }
    energy -= 25;
    unsigned int randDamage[5] = {10, 20, 30, 40, 50};
    std::string randSkill[5] = {"punch", "kick", "stick", "flourescent light", "stone"};
    srand(clock());
    int random = rand() % 5;
        std::cout <<
    "FR4G-TP "<< this->name << " attacks " << target <<
    " at " << randSkill[random] << ", causing " << randDamage[random] << " points of damage! holy!" << std::endl;
    return randDamage[random];
}