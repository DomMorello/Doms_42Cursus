#include "./Contact.hpp"

void    Contact::input_info(void) {
    for (int i = 0; i < FIELD_NUM; i++)
    {
        std::cout<<field[i]<<" : ";
        std::getline(std::cin, info[i]);
		if (std::cin.eof())
			exit(-1);
	}
}

void    Contact::print_info(void) {
    std::cout << "\n\n-------------------------------\n\n";
    for (int i = 0; i < FIELD_NUM; i++)
        std::cout << field[i] << " : " << info[i] << std::endl;
    std::cin.ignore();    
}

void    Contact::show_header(void) {
    for (int i = 0; i < 3; i++)
    {
        std::cout << "|";
        if (this->info[i].length() > 10)
            std::cout << this->info[i].substr(0, 9) << ".";
        else
            std::cout << std::setw(10) << this->info[i];
    }
    std::cout << "|" << std::endl;
}