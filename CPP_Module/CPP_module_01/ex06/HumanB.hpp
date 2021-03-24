#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "./Weapon.hpp"

class HumanB {
    public:
        HumanB(std::string _name);
        void attack();

    private:
        Weapon      weapon;
        std::string name;
};

#endif