#include "./Human.hpp"

Human::Human() { }

std::string Human::identify() const {
    return (brain.identify());
}

//�������� return�����ν� ��Ȯ�� ���� �ּҰ��� return�Ѵ�.
//�׳� brain�� �����ϸ� ������ �ּҰ��� �ٸ� ���� return��.
//c++ ǥ�ؿ����� return���� �ӽú����� ��Ƽ� ��ȯ�Ѵ�.
//�׷��� Ŭ���� �ɹ������� �״�� ���� �ּҰ��� ���� �� ������
//return�� �ϸ鼭 �ӽú����� �ּҰ��� ���� ������
//return brain; �̷������� �ϸ� �ּҰ��� �޶����� ���̴�.
const Brain&   Human::getBrain() const {
    const Brain& ref = brain;
    return (ref);
}