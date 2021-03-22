#include "./ZombieEvent.hpp"

void	ZombieEvent::setZombieType(std::string type) {
	this->type = type;
}

Zombie* ZombieEvent::newZombie(std::string name) {
	Zombie *zombie = new Zombie(name, type);
	return (zombie);
}

void    ZombieEvent::randomChump() {
	srand((unsigned int)time(NULL));
	Zombie	zombie(c_names[rand() % 10], type);

	zombie.announce();
}