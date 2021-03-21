#include "Directory.hpp"

Directory::Directory(void) : idx(0) { }

void    Directory::addContact(void) {
    if (idx == SIZE)
        std::cout << "Error: Directory is full" << std::endl;
    else
        contacts[idx++].input_info();
}

void    Directory::searchContact(void) {
    int input;

    std::cout<<"     index|first name| last name|  nickname\n";
	std::cout<<"-------------------------------------------\n";
    for (int i = 0; i < idx; i++)
    {
        std::cout << std::setw(10) << i << "|";
        contacts[i].show_header();
    }
    std::cout << std::endl << "Select Index : ";
    std::cin >> input;
    if (std::cin.eof())
        exit(-1);
    if (input < 0 || input >= idx || std::cin.fail())
    {
        std::cout << "Error: Invalid input\n" << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
    else
        contacts[input].print_info();
}