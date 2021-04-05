#ifndef SQUAD_HPP
#define SQUAD_HPP

#include "./ISquad.hpp"
#include "./TacticalMarine.hpp"

class Squad : public ISquad {
    private:
        int count;
        ISpaceMarine **unit;
        // push를 통해서 포인터를 넣기 떄문에 포인터의 배열로 선언
        // 추상클래스는 객체를 만들 수 없고 main에서 다형성을 사용하기 때문에 포인터배열이 필요.

    public:
        Squad();
        Squad(const Squad & squad);
        virtual ~Squad();
        Squad& operator=(const Squad & squad);

        virtual int getCount() const;
        virtual ISpaceMarine* getUnit(int idx) const;
        virtual int push(ISpaceMarine* newOne);
};

#endif