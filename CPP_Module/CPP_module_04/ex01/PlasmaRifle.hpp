#ifndef PLASMARIFLE_HPP
#define PLASMARIFLE_HPP

#include "./AWeapon.hpp"

class PlasmaRifle : public AWeapon{
    public:
        PlasmaRifle();
        PlasmaRifle(const PlasmaRifle & rifle);
        virtual ~PlasmaRifle();
        PlasmaRifle& operator=(const PlasmaRifle & rifle);
        
        void attack() const;
};

#endif