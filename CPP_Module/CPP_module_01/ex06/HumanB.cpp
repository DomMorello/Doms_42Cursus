#include "./HumanB.hpp"

HumanB::HumanB(std::string _name) : name(_name) { }

void setWeapon(Weapon& _weapon) {
    weapon = _weapon;
}

void    HumanB::attack() {
    std::cout << name << " attacks with his ";
    std::cout << weapon.getType() << std::endl;
}