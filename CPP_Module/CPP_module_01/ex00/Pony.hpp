#ifndef PONY_HPP
#define PONY_HPP

#include <iostream>
#include <string>

class Pony {
    public:
        Pony(std::string _name);
        virtual ~Pony();
        
    private:
        std::string name;
};

#endif