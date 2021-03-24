#include "./Human.hpp"

Human::Human() { }

std::string Human::identify() const {
    return (brain.identify());
}

//참조값을 return함으로써 정확히 같은 주소값을 return한다.
//그냥 brain을 리턴하면 원래의 주소값과 다른 값이 return됨.
//c++ 표준에서는 return값을 임시변수에 담아서 반환한다.
//그래서 클래스 맴버변수를 그대로 쓰면 주소값이 같을 것 같지만
//return을 하면서 임시변수의 주소값을 갖기 때문에
//return brain; 이런식으로 하면 주소값이 달라지는 것이다.
const Brain&   Human::getBrain() const {
    const Brain& ref = brain;
    return (ref);
}