#include "./Pony.hpp"

Pony::Pony(std::string _name) : name(_name) {
    std::cout << this->name << " is created" << std::endl;
}

Pony::~Pony() {
    std::cout << this->name << " is gone" << std::endl;
}