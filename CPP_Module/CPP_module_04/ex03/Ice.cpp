#include "./Ice.hpp"

Ice::Ice() : AMateria("ice") { }

Ice::Ice(const Ice & ice) : AMateria("ice") {
    *this = ice;
}

Ice::~Ice() { }

Ice& Ice::operator=(const Ice & ice) {
    this->_type = ice._type;
    this->_xp = ice._xp;
    return *this;
}

AMateria* Ice::clone() const {
    return (new Ice(*this));
}

void Ice::use(ICharacter& target) {
    AMateria::use(target);
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}