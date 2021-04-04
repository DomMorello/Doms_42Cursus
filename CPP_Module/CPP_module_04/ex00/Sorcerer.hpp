#ifndef SORVERER_HPP
#define SORVERER_HPP

#include <iostream>
#include <string>
#include "./Victim.hpp"

class Sorcerer {
    public:
        Sorcerer(std::string _name, std::string _title);
        Sorcerer(const Sorcerer & sorcerer);
        virtual ~Sorcerer();
        Sorcerer& operator=(const Sorcerer & sorcerer);
  
        const std::string getName(void) const;
        const std::string getTitle(void) const;
        void polymorph(Victim const &) const;
    private:
        Sorcerer();

        std::string name;
        std::string title;
};

std::ostream& operator<<(std::ostream& os, const Sorcerer& sorcerer);

#endif
