#ifndef HUAN_HPP
#define HUAN_HPP

#include "./Brain.hpp"

class Human {
	public:
		Human();	//windows에서는 기본생성자 없으면 컴파일 에러
		std::string		identify() const;
        const Brain&	getBrain() const;
		
	private:
        const Brain brain;
};

#endif