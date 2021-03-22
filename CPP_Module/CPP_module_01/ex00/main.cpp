#include "./Pony.hpp"

void    ponyOnTheHeap(std::string name) {
    Pony *pony = new Pony(name);
    delete(pony);
}

void    ponyOnTheStack(std::string name) {
    Pony pony(name);
}

int main(void) {
    std::cout << "--- ponyOnTheHeap ---" << std::endl;
    ponyOnTheHeap("Mr.Heap");

    std::cout << "--- ponyOnTheStack ---" << std::endl;
    ponyOnTheStack("Mr.Stack");
    return (0);
}