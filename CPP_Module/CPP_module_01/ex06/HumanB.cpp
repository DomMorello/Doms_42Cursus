#include "./HumanB.hpp"

HumanB::HumanB(std::string _name) : name(_name) { }

void    HumanB::setWeapon(Weapon& _weapon) {
    //포인터에 담아야 하기 때문에 변수명 자체가 아니라
    //변수의 주소값을 담아야 한다.
    weapon = &_weapon;
}

void    HumanB::attack() {
    std::cout << name << " attacks with his ";
    std::cout << weapon->getType() << std::endl;
}