#ifndef AMATERTIA_HPP
#define AMATERTIA_HPP

#include <iostream>
#include <string>
#include "ICharacter.hpp"

class AMateria {
    protected:
        std::string _type;
        unsigned int _xp;
    public:
        AMateria();
        AMateria(std::string const & type);
        AMateria(const AMateria & materia);
        virtual ~AMateria();
        AMateria& operator=(const AMateria & materia);

        std::string const & getType() const;
        unsigned int getXP() const;
        virtual AMateria* clone() const = 0;
        virtual void use(ICharacter& target);
};

#endif