#include "TacticalMarine.hpp"

TacticalMarine::TacticalMarine() {
    std::cout << "Tactical Marine ready for battle!" << std::endl;
}

TacticalMarine::TacticalMarine(const TacticalMarine & marine) {
    *this = marine;
    std::cout << "Tactical Marine ready for battle!" << std::endl;
}

TacticalMarine::~TacticalMarine() {
    std::cout << "Aaargh..." << std::endl;
}

TacticalMarine& TacticalMarine::operator=(const TacticalMarine & marine) {
    (void)marine;
    return *this;
}

ISpaceMarine* TacticalMarine::clone() const {
    //복사 생성자를 이용해서 현재 객체를 만들어서 (복제되어)리턴한다.
    return (new TacticalMarine(*this));
}

void TacticalMarine::battleCry() const {
    std::cout << "For the holy PLOT!" << std::endl;
}

void TacticalMarine::rangedAttack() const {
    std::cout << "* attacks with a bolter *" << std::endl;
}

void TacticalMarine::meleeAttack() const {
    std::cout << "* attacks with a chainsword *" << std::endl;
}