#ifndef SUPERMUTANT_HPP
#define SUPERMUTANT_HPP

#include "./Enemy.hpp"

class SuperMutant : public Enemy {
    public:
        SuperMutant();
        SuperMutant(const SuperMutant & mutant);
        virtual ~SuperMutant();
        SuperMutant& operator=(const SuperMutant & mutant);

        void takeDamage(int damage);
};

#endif