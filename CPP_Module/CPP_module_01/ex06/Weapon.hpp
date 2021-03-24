#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <string>

class Weapon {
    public:
        Weapon(std::string _type = "notype");
        const std::string& getType();
        void setType(const std::string _type);

    private:
        std::string type;
};

#endif