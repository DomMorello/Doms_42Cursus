#ifndef TACTICALMARINE_HPP
#define TACTICALMARINE_HPP

#include "./ISpaceMarine.hpp"

class TacticalMarine : public ISpaceMarine {
    public:
        // ~TacticalMarine();
        
        virtual ISpaceMarine* clone() const;
        virtual void battleCry() const;
        virtual void rangedAttack() const;
        virtual void meleeAttack() const;
};

#endif