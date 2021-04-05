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

        //Peon의 경우 Sorcerer에서 Victim으로 매개변수를 받기 때문에
        //virtual로 해줘야 Peon에 오버라이딩된 함수로 실행이 된다.
        virtual void getPolymorphed() const;
    protected:
        std::string name;
};

std::ostream& operator<<(std::ostream& os, const Victim& victim);

#endif
