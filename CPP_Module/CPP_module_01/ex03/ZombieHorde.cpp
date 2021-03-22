#include "./ZombieHorde.hpp"

ZombieHorde::ZombieHorde(int n) {
    this->size = n;
    srand((unsigned int)time(NULL));
    zombies = new Zombie[n];

    for (int i = 0; i < n; i++)
    {
        zombies[i].setName(c_names[rand() % 10]);
        if (i % 2)
            zombies[i].setType("female");
        else
            zombies[i].setType("male");
    }
}

ZombieHorde::~ZombieHorde() {
    delete[] zombies;
    std::cout << "free zombies!!!" << std::endl;
}

void    ZombieHorde::announce() {
    for (int i = 0; i < this->size; i++)
        zombies[i].announce();
}