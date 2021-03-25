#include "./Weapon.hpp"

Weapon::Weapon(std::string _type) : type(_type) { }

const std::string& Weapon::getType() {
    return (type);
}

//type 이 const면 set을 할 수가 없다. list initializer로 초기화가
//된 이후에는 수정할 수 없다.
void    Weapon::setType(const std::string _type) {
    type = _type;
}