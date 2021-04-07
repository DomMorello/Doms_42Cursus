#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
    private:
        int _cur_idx;
        AMateria *_materia[4];
    public:
        MateriaSource();
        MateriaSource(const MateriaSource & source);
        virtual ~MateriaSource();
        MateriaSource& operator=(const MateriaSource & source);

        virtual void learnMateria(AMateria* m);
        virtual AMateria* createMateria(std::string const & type);
};

#endif