#include "./Sorcerer.hpp"
#include "./Victim.hpp"
#include "./Peon.hpp"

int main()
{
    {
        Sorcerer robert("Robert", "the Magnificent");
        // Sorcerer sorcerer;

        Victim jim("Jimmy");
        Peon joe("Joe");
        
        std::cout << robert << jim << joe;
        
        robert.polymorph(jim);
        robert.polymorph(joe);
    }
    {
        std::cout << "----------------------" << std::endl;
        Sorcerer steven("Steven", "the Socerer Supreme");

        Victim *james = new Victim("James");
        Victim *jin = new Peon("Jin");

        std::cout << steven << *james << *jin;

        steven.polymorph(*james);
        steven.polymorph(*jin);

        delete james;
        delete jin;
    }
    return 0;
}
