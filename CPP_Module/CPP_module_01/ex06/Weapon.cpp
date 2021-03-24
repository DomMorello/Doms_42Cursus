#include "./Weapon.hpp"

Weapon::Weapon(std::string _type) : type(_type) { }

const std::string& Weapon::getType() {
    const std::string& ref = type;
    return (ref);
}

//type �� const�� set�� �� ���� ����. list initializer�� �ʱ�ȭ��
//�� ���Ŀ��� ������ �� ����.
void    Weapon::setType(std::string _type) {
    type = _type;
}