#include "./Character.hpp"

Character::Character()
    :
    name("unknown"),
    AP(0),
    weapon(NULL)
    { }

Character::Character(std::string const & name)
    : name(name), AP(40) { }

Character::~Character() { }

Character::Character(const Character & character) {
    *this = character;
}

Character& Character::operator=(const Character & character) {
    name = character.name;
    AP = character.AP;
    weapon = character.weapon;
    return *this;
}

void Character::recoverAP() {
    AP += 10;
    if (AP > 40)
        AP = 40;
}

void Character::equip(AWeapon* weapon) {
    this->weapon = weapon;
}

void Character::attack(Enemy* enemy) {
    if (AP < weapon->getAPCost() || weapon == NULL)
        return ;
    std::cout << name << " attacks " << enemy->getType()
    << " with a " <<  weapon->getName() << std::endl;
    weapon->attack();
    AP -= weapon->getAPCost();
    enemy->takeDamage(weapon->getDamage());
    if (enemy->getHP() <= 0)
        enemy->~Enemy();
}

const std::string Character::getName() const {
    return name;
}

int Character::getAP() const {
    return AP;
}

const AWeapon* Character::getWeapon() const {
    return weapon;
}

std::ostream& operator<<(std::ostream& os, const Character &character) {
    if (character.getWeapon() != NULL)
    {
        os << character.getName() << " has " << character.getAP()
        << " AP and wields a " <<  character.getWeapon()->getName() << std::endl; 
    }
    else
    {
        os << character.getName() << " has " << character.getAP()
        << " AP and is unarmed" << std::endl;
    }
    return os;
}