#include "./PowerFist.hpp"

PowerFist::PowerFist() : AWeapon("Power Fist", 8, 50) { }

PowerFist::PowerFist(const PowerFist & fist) : AWeapon(fist) { }

PowerFist::~PowerFist() { }

PowerFist& PowerFist::operator=(const PowerFist & fist) {
    name = fist.name;
    apcost = fist.apcost;
    damage = fist.damage;
    return *this;
}

void PowerFist::attack() const {
    std::cout << "* pschhh... SBAM! *" << std::endl;
}