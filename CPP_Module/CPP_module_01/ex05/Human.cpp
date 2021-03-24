#include "./Human.hpp"

std::string Human::identify() const {
    return (brain.identify());
}

Brain   Human::getBrain() const {
    return (brain);
}