#include "easyfind.hpp"

int main()
{
    std::vector<int> vec;
    std::list<int> li;
    std::deque<int> deq;
    std::set<int> sett;

    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i + 100);
        li.push_back(i + 100);
        deq.push_back(i + 100);
        sett.insert(i + 100);
    }
    
    //vector 찾을 수 있는 경우
    std::vector<int>::iterator itr1 = easyfind(vec, 104);
    if (itr1 != vec.end())
        std::cout << "vector: found!" << std::endl;
    else
        std::cout << "vector: cannot find!" << std::endl;
    //찾을 수 없는 경우
    itr1 = easyfind(vec, 98);
    if (itr1 != vec.end())
        std::cout << "vector: found!" << std::endl;
    else
        std::cout << "vector: cannot find!" << std::endl;

    //list 찾을 수 있는 경우
    std::list<int>::iterator itr2 = easyfind(li, 104);
    if (itr2 != li.end())
        std::cout << "list: found!" << std::endl;
    else
        std::cout << "list: cannot find!" << std::endl;
    //찾을 수 없는 경우
    itr2 = easyfind(li, 98);
    if (itr2 != li.end())
        std::cout << "list: found!" << std::endl;
    else
        std::cout << "list: cannot find!" << std::endl;

    //deque 찾을 수 있는 경우
    std::deque<int>::iterator itr3 = easyfind(deq, 104);
    if (itr3 != deq.end())
        std::cout << "deque: found!" << std::endl;
    else
        std::cout << "deque: cannot find!" << std::endl;
    //찾을 수 없는 경우
    itr3 = easyfind(deq, 98);
    if (itr3 != deq.end())
        std::cout << "deque: found!" << std::endl;
    else
        std::cout << "deque: cannot find!" << std::endl;
    
    //set 찾을 수 있는 경우
    std::set<int>::iterator itr4 = easyfind(sett, 104);
    if (itr4 != sett.end())
        std::cout << "set: found!" << std::endl;
    else
        std::cout << "set: cannot find!" << std::endl;
    //찾을 수 없는 경우
    itr4 = easyfind(sett, 98);
    if (itr4 != sett.end())
        std::cout << "set: found!" << std::endl;
    else
        std::cout << "set: cannot find!" << std::endl;
}