#include "./Peon.hpp"

Peon::Peon() : Victim() {
    std::cout << "Zog zog." << std::endl;
}

Peon::Peon(std::string name) : Victim(name) {
    std::cout << "Zog zog." << std::endl;
}

Peon::Peon(const Peon & peon) {
    *this = peon;
}

Peon::~Peon() {
    std::cout << "Bleuark..." << std::endl;
}

Peon& Peon::operator=(const Peon & peon) {
    name = peon.name;
    return *this;
}

void Peon::getPolymorphed() const {
    std::cout << name << " has been turned into a pink pony!" << std::endl;
}