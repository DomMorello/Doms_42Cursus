#include "./Sorcerer.hpp"

Sorcerer::Sorcerer(std::string _name, std::string _title)
    : name(_name), title(_title) {
        std::cout << name << ", " << title << ", is born!" << std::endl;   
    }

Sorcerer::Sorcerer(const Sorcerer & sorcerer) {
    std::cout << name << ", " << title << ", is born!" << std::endl;
    *this = sorcerer;
}

Sorcerer& Sorcerer::operator=(const Sorcerer & sorcerer) {
    name = sorcerer.name;
    title = sorcerer.title;
    return *this;
}

Sorcerer::~Sorcerer() {
    std::cout  << name << ", " << title
    << ", is dead. Consequences will never be the same!"
    << std::endl;
}

const std::string Sorcerer::getName() const {
    return name;
}

const std::string Sorcerer::getTitle() const {
    return title;
}

void Sorcerer::polymorph(Victim const &) const {
    
}

std::ostream& operator<<(std::ostream& os, const Sorcerer& sorcerer) {
    os << "I am " << sorcerer.getName() << ", "
    << sorcerer.getTitle() << ", and I like Ponies!" << std::endl;
    return os;
}




