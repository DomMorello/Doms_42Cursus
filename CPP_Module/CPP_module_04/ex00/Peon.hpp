#ifndef PEON_HPP
#define PEON_HPP

#include <iostream>
#include <string>
#include "./Victim.hpp"

class Peon : public Victim {
    public:
        Peon();
        Peon(std::string _name);
        Peon(const Peon & peon);
        virtual ~Peon();
        Peon& operator=(const Peon & peon);
        const std::string getName(void) const;

        void getPolymorphed() const;
    private:
        std::string name;
};

std::ostream& operator<<(std::ostream& os, const Peon& peon);

#endif