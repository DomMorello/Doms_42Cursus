#include "./Human.hpp"

Human::Human() { }

std::string Human::identify() const {
    return (brain.identify());
}

//�������� return�����ν� ��Ȯ�� ���� �ּҰ��� return�Ѵ�.
//�׳� brain�� �����ϸ� ������ �ּҰ��� �ٸ� ���� return��.
const Brain&   Human::getBrain() const {
    const Brain& ref = brain;
    return (ref);
}