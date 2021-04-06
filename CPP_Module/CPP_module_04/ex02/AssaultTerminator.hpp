#ifndef ASSAULTTERMINATOR_HPP
#define ASSAULTTERMINATOR_HPP

#include "./ISpaceMarine.hpp"

class AssaultTerminator : public ISpaceMarine {
    public:
        AssaultTerminator();
        AssaultTerminator(const AssaultTerminator & terminator);
        virtual ~AssaultTerminator();
        AssaultTerminator& operator=(const AssaultTerminator & terminator);
        
        virtual ISpaceMarine* clone() const;
        virtual void battleCry() const;
        virtual void rangedAttack() const;
        virtual void meleeAttack() const;
};

#endif