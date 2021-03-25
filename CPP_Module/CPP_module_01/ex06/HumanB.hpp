#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "./Weapon.hpp"

class HumanB {
    public:
        HumanB(std::string _name);
        //참조자로 선언을 해야 값만 바뀌는 것이 아니라 
        //실제 그 객체의 주소값을 포인터에 담을 수 있다.
        void setWeapon(Weapon& _weapon);
        void attack();

    private:
        //여기서는 참조자로 할 수 없는 이유가 참조자로 하게 되면
        //선언과 동시에 초기화가 돼야 하는데 main에서
        //요구하는 상황에서는 초기화를 진행할 수 없다.
        Weapon      *weapon;
        std::string name;
};

#endif