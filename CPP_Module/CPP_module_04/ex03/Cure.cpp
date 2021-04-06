#include "./Cure.hpp"

Cure::Cure() : AMateria("cure") { }

Cure::Cure(const Cure & cure) : AMateria("cure") {
    *this = cure;
}

Cure::~Cure() { }

Cure& Cure::operator=(const Cure & cure) {
    this->_type = cure._type;
    this->_xp = cure._xp;
    return *this;
}

AMateria* Cure::clone() const {
    return (new Cure(*this));
}

void Cure::use(ICharacter& target) {
    AMateria::use(target);
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}