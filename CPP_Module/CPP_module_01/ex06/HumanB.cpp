#include "./HumanB.hpp"

HumanB::HumanB(std::string _name) : name(_name) { }

void    HumanB::setWeapon(Weapon& _weapon) {
    //�����Ϳ� ��ƾ� �ϱ� ������ ������ ��ü�� �ƴ϶�
    //������ �ּҰ��� ��ƾ� �Ѵ�.
    weapon = &_weapon;
}

void    HumanB::attack() {
    std::cout << name << " attacks with his ";
    std::cout << weapon->getType() << std::endl;
}