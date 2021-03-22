#include "./Zombie.hpp"

Zombie::Zombie() : name("unknown name"), type("unknown name") { }

Zombie::Zombie(std::string _name, std::string _type) {
	this->name = _name;
	this->type = _type;
}

void	Zombie::announce() {
	std::cout << "<" << this->name <<
	" (" << this->type << ")> Braiiiiiiinnnssss..." << std::endl;
}

void	Zombie::setName(std::string name) {
	this->name = name;
}

void	Zombie::setType(std::string type) {
	this->type = type;
}

