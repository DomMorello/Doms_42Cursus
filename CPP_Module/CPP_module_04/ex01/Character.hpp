#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include <string>
#include "./AWeapon.hpp"
#include "./Enemy.hpp"

class Character {
    private:
        std::string name;
        int AP;
        AWeapon *weapon;
    public:
        Character();
        Character(std::string const & name);
        Character(const Character & character);
        ~Character();
        Character& operator=(const Character & character);

        void recoverAP();
        void equip(AWeapon* weapon);
        void attack(Enemy* enemy);
        const std::string getName() const;
        int getAP() const;
        const AWeapon* getWeapon() const;
};

std::ostream& operator<<(std::ostream& os, const Character &character);

#endif