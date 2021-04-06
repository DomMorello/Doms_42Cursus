#include "./AMateria.hpp"

AMateria::AMateria() : _type("unknown"), _xp(0) { }

AMateria::AMateria(std::string const & type) : _type(type), _xp(0) { }

AMateria::AMateria(const AMateria & materia) {
    *this = materia;
}

AMateria::~AMateria() { }

AMateria& AMateria::operator=(const AMateria & materia) {
    _type = materia._type;
    _xp = materia._xp;
    return *this;
}

std::string const & AMateria::getType() const {
    return _type;
}

unsigned int AMateria::getXP() const {
    return _xp;
}

void AMateria::use(ICharacter& target) {
    (void)target;
    this->_xp += 10;
}