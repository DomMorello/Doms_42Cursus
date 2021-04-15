#include "mutantstack.hpp"
#include "mutantstack.cpp"

int main()
{
    MutantStack<int> mstack;
    
    mstack.push(5);
    mstack.push(17);
    
    std::cout << "top: " << mstack.top() << std::endl;
    
    mstack.pop();
    
    std::cout << "size: " << mstack.size() << std::endl;
    
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    //전체 출력
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);
    std::cout << "copied size: " << s.size() << std::endl;

    std::cout << "-------------------------" << std::endl;

    MutantStack<std::string> ms;
    ms.push("donglee");
    ms.push("domas");
    ms.push("morello");
    ms.push("hello");
    ms.push("world");

    ms.pop();
    ms.pop();

    MutantStack<std::string>::iterator it2 = ms.begin();
    MutantStack<std::string>::iterator ite2 = ms.end();
    while (it2 != ite2)
    {
        std::cout << *it2 << std::endl;
        ++it2;
    }
    return 0;
}