#include "./ZombieEvent.hpp"

int main() {
	Zombie zombie1;
    zombie1.announce();
    
    Zombie zombie2("donglee", "male");
    zombie2.announce();

    ZombieEvent event1;
    event1.setZombieType("female");
    Zombie *zombie3 = event1.newZombie("hello");
    zombie3->announce();
    delete zombie3;

    ZombieEvent event2;
    event2.setZombieType("male");
    event2.randomChump();
    
    return 0;
}