#ifndef PEON_HPP
#define PEON_HPP

#include "./Victim.hpp"

class Peon : public Victim {
    public:
        Peon();
        Peon(std::string _name);
        Peon(const Peon & peon);
        virtual ~Peon();
        Peon& operator=(const Peon & peon);

        void getPolymorphed() const;
};

#endif