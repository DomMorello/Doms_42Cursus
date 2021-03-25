#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "./Weapon.hpp"

class HumanB {
    public:
        HumanB(std::string _name);
        //�����ڷ� ������ �ؾ� ���� �ٲ�� ���� �ƴ϶� 
        //���� �� ��ü�� �ּҰ��� �����Ϳ� ���� �� �ִ�.
        void setWeapon(Weapon& _weapon);
        void attack();

    private:
        //���⼭�� �����ڷ� �� �� ���� ������ �����ڷ� �ϰ� �Ǹ�
        //����� ���ÿ� �ʱ�ȭ�� �ž� �ϴµ� main����
        //�䱸�ϴ� ��Ȳ������ �ʱ�ȭ�� ������ �� ����.
        Weapon      *weapon;
        std::string name;
};

#endif