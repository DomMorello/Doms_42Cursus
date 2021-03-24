#include "./HumanA.hpp"

HumanA::HumanA(std::string _name, Weapon& _weapon) : weapon(_weapon) {
    name = _name;
}

void    HumanA::attack() {
    std::cout << name << " attacks with his ";
    std::cout << weapon.getType() << std::endl;
}