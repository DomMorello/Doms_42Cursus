#include "./Directory.hpp"

int main(void)
{
    Directory directory;
    std::string input;

    while (true)
    {
        std::cout << "type 1.ADD 2.SEARCH 3.EXIT : ";
        std::getline(std::cin, input);
        if (std::cin.eof())
			return (-1);
        if (input == "ADD")
            directory.addContact();
        else if (input == "SEARCH")
            directory.searchContact();
        else if (input == "EXIT")
            return (-1);
        else
            std::cout << "Error: Wrong input!" << std::endl;
    }
    return (-1);
}