#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "./Weapon.hpp"

class HumanA {
    public:
    //���⼭ �Ű������� & ���۷����� ������ ������
    //dangling warning�� ���. �����ڰ� ������鼭
    //�ӽ������� ���ÿ� �ִ� �Ű����� �޸𸮴� �����ڰ�
    //�����鼭 �Բ� �޸𸮿��� ������µ�
    //�� �޸𸮸� reference�� �����Ϸ��� �ϱ� ������
    //������ �߻��ϴ� ���̴�. �׷��� &�� ����� �Ѵ�.
        HumanA(std::string _name, Weapon& _weapon);
        void attack();

    private:
        Weapon&     weapon;
        //reference�� �ϴ� ������ setType()�Լ���
        //�������� �� Weapon��ü�� �ɹ������� �ٲ�µ�
        //�� ��ȭ�� �� ��ü�� ���� �ִ� Human��ü����
        //������ �ž� �ϱ� ������ reference�� �ߴ�.
        std::string name;
};

#endif