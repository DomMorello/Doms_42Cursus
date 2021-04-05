#include "./PlasmaRifle.hpp"

PlasmaRifle::PlasmaRifle() : AWeapon("Plasma Rifle", 5, 21) { }

PlasmaRifle::PlasmaRifle(const PlasmaRifle & rifle) : AWeapon(rifle) { }

PlasmaRifle::~PlasmaRifle() { }

PlasmaRifle& PlasmaRifle::operator=(const PlasmaRifle & rifle) {
    name = rifle.name;
    apcost = rifle.apcost;
    damage = rifle.damage;
    return *this;
}

void PlasmaRifle::attack() const {
    std::cout << "* piouuu piouuu piouuu *" << std::endl;
}