#include "./Peon.hpp"

Peon::Peon() : name("unknown") {
    std::cout << "Some random peon called " << name << " just appeared!" << std::endl;
}

Peon::Peon(std::string name) : name(name) {
    std::cout << "Some random peon called " << name << " just appeared!" << std::endl;
}

Peon::Peon(const Peon & peon) {
    *this = peon;
}

Peon::~Peon() {
    std::cout << "Peon " << name << " just died for no apparent reason!" << std::endl;
}

Peon& Peon::operator=(const Peon & peon) {
    name = peon.name;
    return *this;
}

const std::string Peon::getName() const {
    return name;
}

void Peon::getPolymorphed() const {
    std::cout << name << " has been turned into a cute little sheep!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Peon& peon) {
    os << "I'm" << peon.getName() << " and I like otters!" << std::endl;
    return os;
}