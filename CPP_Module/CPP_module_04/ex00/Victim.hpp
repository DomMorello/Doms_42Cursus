#ifndef VIRTIM_HPP
#define VIRTIM_HPP

#include <iostream>
#include <string>

class Victim {
    public:
        Victim();
        Victim(std::string _name);
        Victim(const Victim & victim);
        virtual ~Victim();
        Victim& operator=(const Victim & victim);
        const std::string getName(void) const;

        //Peon�� ��� Sorcerer���� Victim���� �Ű������� �ޱ� ������
        //virtual�� ����� Peon�� �������̵��� �Լ��� ������ �ȴ�.
        virtual void getPolymorphed() const;
    protected:
        std::string name;
};

std::ostream& operator<<(std::ostream& os, const Victim& victim);

#endif
