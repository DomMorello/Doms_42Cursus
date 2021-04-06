#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
    private:

    
    public:
        MateriaSource();
        MateriaSource(const MateriaSource & source);
        virtual ~MateriaSource();
        MateriaSource& operator=(const MateriaSource & source);

        virtual void learnMateria(AMateria*);
        virtual AMateria* createMateria(std::string const & type);
};

#endif