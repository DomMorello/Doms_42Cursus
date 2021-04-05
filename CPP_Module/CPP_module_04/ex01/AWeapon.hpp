#ifndef AWEAPON_HPP
#define AWEAPON_HPP

#include <iostream>
#include <string>

class AWeapon {
    protected:
        std::string name;
        int apcost;
        int damage;

    public:
        AWeapon();
        AWeapon(std::string const & name, int apcost, int damage);
        AWeapon(const AWeapon & weapon);
        virtual ~AWeapon();
        AWeapon& operator=(const AWeapon & weapon);

        const std::string getName() const;
        int getAPCost() const;
        int getDamage() const;
        virtual void attack() const = 0;
};

#endif