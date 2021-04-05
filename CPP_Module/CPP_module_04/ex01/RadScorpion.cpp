#include "./RadScorpion.hpp"

RadScorpion::RadScorpion() : Enemy(80, "RadScorpion") {
    std::cout << "* click click click *" std::endl;
}

RadScorpion::RadScorpion(const RadScorpion & scorpion) : Enemy(scorpion) {
    std::cout << "* click click click *" std::endl;
}

RadScorpion::~RadScorpion() {
    std::cout << "* SPROTCH *" << std::endl;
}

RadScorpion& RadScorpion::operator=(const RadScorpion & scorpion) {
    HP = scorpion.HP;
    type = scorpion.type;
    return *this;
}