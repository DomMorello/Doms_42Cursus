#include "AssaultTerminator.hpp"

AssaultTerminator::AssaultTerminator() {
    std::cout << "* teleports from space *" << std::endl;
}

AssaultTerminator::AssaultTerminator(const AssaultTerminator & terminator) {
    *this = terminator;
    std::cout << "* teleports from space *" << std::endl;
}

AssaultTerminator::~AssaultTerminator() {
    std::cout << "I'll be back..." << std::endl;
}

AssaultTerminator& AssaultTerminator::operator=(const AssaultTerminator & terminator) {
    (void)terminator;
    return *this;
}

ISpaceMarine* AssaultTerminator::clone() const {
    //복사 생성자를 이용해서 현재 객체를 만들어서 (복제되어)리턴한다.
    return (new AssaultTerminator(*this));
}

void AssaultTerminator::battleCry() const {
    std::cout << "This code is unclean. PURIFY IT!" << std::endl;
}

void AssaultTerminator::rangedAttack() const {
    std::cout << "* does nothing *" << std::endl;
}

void AssaultTerminator::meleeAttack() const {
    std::cout << "* attacks with chainfists *" << std::endl;
}