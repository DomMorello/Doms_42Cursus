#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "./Weapon.hpp"

class HumanA {
    public:
    //여기서 매개변수로 & 레퍼런스를 해주지 않으면
    //dangling warning이 뜬다. 생성자가 사라지면서
    //임시적으로 스택에 있는 매개변수 메모리는 생성자가
    //끝나면서 함께 메모리에서 사라지는데
    //그 메모리를 reference로 참조하려고 하기 떄문에
    //에러가 발생하는 것이다. 그래서 &를 해줘야 한다.
        HumanA(std::string _name, Weapon& _weapon);
        void attack();

    private:
        Weapon&     weapon;
        //reference로 하는 이유는 setType()함수를
        //실행했을 때 Weapon객체의 맴버변수가 바뀌는데
        //이 변화가 그 객체를 갖고 있는 Human객체에도
        //적용이 돼야 하기 때문에 reference로 했다.
        std::string name;
};

#endif