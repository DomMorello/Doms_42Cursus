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
    if (AP <= 0)
        return ;
    if (weapon != NULL)
    {
        weapon->attack();
        std::cout << name << " attacks " << enemy->getType()
        << " with a " <<  weapon->getName() << std::endl;
    }
    enemy->takeDamage(weapon->getDamage());
    if (enemy->getHP() <= 0)
        delete enemy;
}

const std::string Character::getName() const {

}

ostream& operator<<(ostream& os, const Character &character) {
    os << 
}