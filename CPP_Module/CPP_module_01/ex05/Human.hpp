#ifndef HUAN_HPP
#define HUAN_HPP

#include "./Brain.hpp"

class Human {
	public:
		std::string identify() const;
        Brain       getBrain() const;
	private:
        const Brain brain;
};

#endif