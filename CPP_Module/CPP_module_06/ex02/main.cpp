#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <ctime>

Base* generate(void) {
    srand(clock());

    Base *ret;
    int randNum = rand() % 3;

    if (randNum == 0)
        return ret = new A;
    else if (randNum == 1)
        return ret = new B;
    else if (randNum == 2)
        return ret = new C;
}

void identify_from_pointer(Base * p) {
    //down casting을 할 때 타입이 맞지 않으면
    //NULL을 반환함
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

void identify_from_reference(Base & p) {
    try
    {
        A& a = dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
    }
    catch(const std::exception& e)
    { }
    try
    {
        B& b = dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
    }
    catch(const std::exception& e)
    { }
    try
    {
        C& c = dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
    }
    catch(const std::exception& e)
    { }
}

int main()
{
    Base *child = generate();

    identify_from_pointer(child);
    identify_from_reference(*child);

    delete child;
    return 0;
}