#ifndef HUAN_HPP
#define HUAN_HPP

#include "./Brain.hpp"

class Human {
	public:
		Human();
		std::string		identify() const;
        const Brain&	getBrain() const;
	private:
        const Brain brain;
};

#endif