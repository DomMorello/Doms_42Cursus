#ifndef POWERFIST_HPP
#define POWERFIST_HPP

#include "./AWeapon.hpp"

class PowerFist : public AWeapon{
    public:
        PowerFist();
        PowerFist(const PowerFist & fist);
        virtual ~PowerFist();
        PowerFist& operator=(const PowerFist & fist);
        
        void attack() const;
};

#endif