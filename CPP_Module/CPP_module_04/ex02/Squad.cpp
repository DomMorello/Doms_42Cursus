#include "./Squad.hpp"

Squad::Squad() : count(0), unit(NULL) { }

Squad::Squad(const Squad & squad) : count(0), unit(NULL) {
    /* TODO: 다른 클래스 먼저 구현해보고 그 함수를 가져다 쓸 수 있는지 보자 */
}

Squad& Squad::operator=(const Squad & squad) {
    //이미 unit이 있으면 먼저 전부 삭제함
    if (unit)
    {
        for (int i = 0; i < count; i++)
            delete unit[i];
        delete unit;
        unit = NULL;
    }
    /* TODO: 연산자 깊은 복사 좀 더 공부해서 구현 */
}

Squad::~Squad() {
    //동적으로 할당된 모든 메모리 해제
    if (unit)
    {
        for (int i = 0; i < count; i++)
            delete unit[i];
        delete unit;
        unit = NULL;
    }
}

int Squad::getCount() const {
    return count;
}

ISpaceMarine* Squad::getUnit(int idx) const {
    if (count == 0 || idx < 0 || idx >= count)
        return NULL;
    return unit[idx];
}

int Squad::push(ISpaceMarine* newOne) {
    // newOne null 체크
    if (newOne != NULL)
    {
        //인자로 들어오는 newOne이 이미 squad에 있는 경우
        //현재 count만 리턴하고 아무 행동도 하지 않는다.
        for (int i = 0; i < count; i++)
        {
            if (unit[i] == newOne)
                return count;
        }
        //기존 squad에 새로 들어오는 newOne이 없는 경우 새로 추가해줘야 하는데
        //크기를 동적으로 하나 더 늘려줘야 하기 때문에 그 전 것까지 복사를 해준다.
        ISpaceMarine **copy = new ISpaceMarine*[count + 1];
        //unit에 먼저 들어온 객체들이 있을 때는 복제를 하고 기존의 unit을 삭제한다.
        if (unit != NULL)
        {
            for (int i = 0; i < count; i++)
                copy[i] = unit[i];
            delete[] unit;
        }
        unit = copy;
        unit[count] = newOne;    //새로운 매개변수 newOne을 맨 뒤에 추가
        count++;
    }
    else    //매개변수가 널일 경우 현재 count 반환
        return count;
}

int main()
{
    Squad s;
}