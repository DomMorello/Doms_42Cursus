#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"

class Character : public ICharacter {
    private:
        std::string _name;
        int _cur_idx;
        AMateria *_inventory[4];

    public:
        Character();
        Character(const std::string name);
        Character(const Character & character);
        virtual ~Character();
        Character& operator=(const Character & character);

        virtual std::string const & getName() const;
        virtual void equip(AMateria* m);
        virtual void unequip(int idx);
        virtual void use(int idx, ICharacter& target);
};

#endif