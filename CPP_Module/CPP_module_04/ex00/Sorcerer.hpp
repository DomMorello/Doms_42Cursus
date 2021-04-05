#ifndef SORVERER_HPP
#define SORVERER_HPP

#include "./Victim.hpp"

class Sorcerer {
    public:
        Sorcerer();
        Sorcerer(std::string _name, std::string _title);
        Sorcerer(const Sorcerer & sorcerer);
        virtual ~Sorcerer();
        Sorcerer& operator=(const Sorcerer & sorcerer);
  
        const std::string getName(void) const;
        const std::string getTitle(void) const;
        void polymorph(Victim const &victim) const;
    private:

        std::string name;
        std::string title;
};

std::ostream& operator<<(std::ostream& os, const Sorcerer& sorcerer);

#endif
