#include "./AWeapon.hpp"

AWeapon::AWeapon()
    :
    name("unknown"),
    apcost(0),
    damage(0)
    { }

AWeapon::AWeapon(std::string const &name, int apcost, int damage)
    :
    name(name),
    apcost(apcost),
    damage(damage)
    { }

AWeapon::AWeapon(const AWeapon & weapon) {
    *this = weapon;
}

AWeapon::~AWeapon() { }

AWeapon& AWeapon::operator=(const AWeapon & weapon) {
    name = weapon.name;
    apcost = weapon.apcost;
    damage = weapon.damage;
    return *this;
}

const std::string AWeapon::getName() const {
    return name;
}

int AWeapon::getAPCost() const {
    return apcost;
}

int AWeapon::getDamage() const {
    return damage;
}