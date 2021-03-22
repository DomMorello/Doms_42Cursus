#include "./ZombieHorde.hpp"

int main(void)
{
    int n;

    while (true)
    {
        std::cin >> n;

        ZombieHorde horde(n);
        horde.announce();
    }
    return 0;
}