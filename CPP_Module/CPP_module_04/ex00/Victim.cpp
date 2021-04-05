#include "./Victim.hpp"

Victim::Victim() : name("unknown") {
    std::cout << "Some random victim called " << name << " just appeared!" << std::endl;
}

Victim::Victim(std::string name) : name(name) {
    std::cout << "Some random victim called " << name << " just appeared!" << std::endl;
}

Victim::Victim(const Victim & victim) {
    *this = victim;
}

Victim::~Victim() {
    std::cout << "Victim " << name << " just died for no apparent reason!" << std::endl;
}

Victim& Victim::operator=(const Victim & victim) {
    name = victim.name;
    return *this;
}

const std::string Victim::getName() const {
    return name;
}

void Victim::getPolymorphed() const {
    std::cout << name << " has been turned into a cute little sheep!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Victim& victim) {
    os << "I'm " << victim.getName() << " and I like otters!" << std::endl;
    return os;
}