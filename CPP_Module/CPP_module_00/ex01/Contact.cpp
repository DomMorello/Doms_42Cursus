#include "./Contact.hpp"

std::string Contact::field[FIELD_NUM] = {
	"First Name",
	"Last Name",
	"Nickname",
	"Login",
	"Postal Address",
	"Email Address",
	"Phone Number",
	"Birthday Date",
	"Favorite Meal",
	"Underwear Color",
	"Darkest Secret"
};

void    Contact::input_info(void) {
    for (int i = 0; i < FIELD_NUM; i++)
    {
        std::cout<<field[i]<<" : ";
        std::getline(std::cin, info[i]);
		if (std::cin.eof())
			exit(-1);
	}
    std::cout << std::endl;
}

void    Contact::print_info(void) {
    std::cout<<"-------------------------------------------\n";
    for (int i = 0; i < FIELD_NUM; i++)
        std::cout << field[i] << " : " << info[i] << std::endl;
    std::cin.ignore();
    std::cout << std::endl;
}

void    Contact::show_header(void) {
    for (int i = 0; i < 3; i++)
    {
        if (this->info[i].length() > 10)
            std::cout << this->info[i].substr(0, 9) << ".";
        else
            std::cout << std::setw(10) << this->info[i];
        std::cout << "|";
    }
    std::cout << std::endl;
}