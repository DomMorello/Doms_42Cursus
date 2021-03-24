#include "./Brain.hpp"

std::string Brain::identify() const {
    std::stringstream ss;
    long adr = (long)this;

    ss << std::showbase << std::uppercase << std::hex << adr;
    return (ss.str());
}