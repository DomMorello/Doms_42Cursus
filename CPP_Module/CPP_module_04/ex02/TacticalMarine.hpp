#ifndef TACTICALMARINE_HPP
#define TACTICALMARINE_HPP

#include "./ISpaceMarine.hpp"

class TacticalMarine : public ISpaceMarine {
    public:
        TacticalMarine();
        TacticalMarine(const TacticalMarine & marine);
        virtual ~TacticalMarine();
        TacticalMarine& operator=(const TacticalMarine & marine);
        
        virtual ISpaceMarine* clone() const;
        virtual void battleCry() const;
        virtual void rangedAttack() const;
        virtual void meleeAttack() const;
};

#endif