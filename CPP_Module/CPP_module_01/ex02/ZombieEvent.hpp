#ifndef ZOMBIEEVENT_HPP
#define ZOMBIEEVENT_HPP

#include "./Zombie.hpp"
#include <ctime>
#include <cstdlib>

class ZombieEvent {
    public:
        void    setZombieType(std::string type);
        Zombie* newZombie(std::string name);
        void    randomChump();
    private:
        std::string type;
};

#endif