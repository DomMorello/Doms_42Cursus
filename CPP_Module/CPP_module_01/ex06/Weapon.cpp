#include "./Weapon.hpp"

Weapon::Weapon(std::string _type) : type(_type) { }

const std::string& Weapon::getType() {
    return (type);
}

//type �� const�� set�� �� ���� ����. list initializer�� �ʱ�ȭ��
//�� ���Ŀ��� ������ �� ����.
void    Weapon::setType(const std::string _type) {
    type = _type;
}