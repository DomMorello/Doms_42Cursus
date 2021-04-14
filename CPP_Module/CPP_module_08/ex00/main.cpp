#include "easyfind.hpp"

//container 전체 출력
template <typename T>
void print(T & container) {
    for (typename T::iterator i = container.begin(); i != container.end(); i++)
        std::cout << *i << std::endl;
}

int main()
{
    std::vector<int> vec;
    std::list<int> li;
    std::deque<int> deq;

    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i + 100);
        li.push_back(i + 100);
        deq.push_back(i + 100);
    }
    
    //vector 찾을 수 있는 경우
    std::vector<int>::iterator itr1 = easyfind(vec, 104);
    if (itr1 != vec.end())
        std::cout << "found!" << std::endl;
    else
        std::cout << "cannot find!" << std::endl;
    //찾을 수 없는 경우
    itr1 = easyfind(vec, 98);
    if (itr1 != vec.end())
        std::cout << "found!" << std::endl;
    else
        std::cout << "cannot find!" << std::endl;

    //list 찾을 수 있는 경우
    std::list<int>::iterator itr2 = easyfind(li, 104);
    if (itr2 != li.end())
        std::cout << "found!" << std::endl;
    else
        std::cout << "cannot find!" << std::endl;
    //찾을 수 없는 경우
    itr2 = easyfind(li, 98);
    if (itr2 != li.end())
        std::cout << "found!" << std::endl;
    else
        std::cout << "cannot find!" << std::endl;

    //deque 찾을 수 있는 경우
    std::deque<int>::iterator itr3 = easyfind(deq, 104);
    if (itr3 != deq.end())
        std::cout << "found!" << std::endl;
    else
        std::cout << "cannot find!" << std::endl;
    //찾을 수 없는 경우
    itr3 = easyfind(deq, 98);
    if (itr3 != deq.end())
        std::cout << "found!" << std::endl;
    else
        std::cout << "cannot find!" << std::endl;
    
    

}