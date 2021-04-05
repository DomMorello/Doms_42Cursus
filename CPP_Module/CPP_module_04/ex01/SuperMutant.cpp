#include "./SuperMutant.hpp"

SuperMutant::SuperMutant() : Enemy(170, "Super Mutant") {
    std::cout << "Gaaah. Me want smash heads!" << std::endl;
}

SuperMutant::SuperMutant(const SuperMutant & mutant) : Enemy(mutant) {
    std::cout << "Gaaah. Me want smash heads!" << std::endl;
}

SuperMutant::~SuperMutant() {
    std::cout << "Aaargh..." << std::endl;
}

SuperMutant& SuperMutant::operator=(const SuperMutant & mutant) {
    HP = mutant.HP;
    type = mutant.type;
    return *this;
}

void SuperMutant::takeDamage(int damage) {
    Enemy::takeDamage(damage - 3);
}