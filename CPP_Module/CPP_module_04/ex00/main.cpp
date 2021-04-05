#include "./Sorcerer.hpp"
#include "./Victim.hpp"
#include "./Peon.hpp"

int main()
{
    Sorcerer robert("Robert", "the Magnificent");
    // Sorcerer sorcerer; 기본 생성자에 접근할 수 없다.

    Victim jim("Jimmy");
    Peon joe("Joe");
    
    std::cout << robert << jim << joe;
    
    robert.polymorph(jim);
    robert.polymorph(joe);
    
    return 0;
}
