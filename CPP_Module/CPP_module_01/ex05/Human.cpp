#include "./Human.hpp"

Human::Human() { }

std::string Human::identify() const {
    return (brain.identify());
}

//참조값을 return함으로써 정확히 같은 주소값을 return한다.
//그냥 brain을 리턴하면 원래의 주소값과 다른 값이 return됨.
const Brain&   Human::getBrain() const {
    const Brain& ref = brain;
    return (ref);
}