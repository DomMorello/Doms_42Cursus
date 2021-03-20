#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>
#include <iomanip>

#define SIZE 8
#define FIELD_NUM 11

class Contact {
    Contact() {
        std::cout << "Contact Constructor!" << std::endl;
    }
    ~Contact() {
        std::cout << "Contact Constructor!" << std::endl;
    }
    public:
        void input_info(void);
        void show_header(void);
        void print_info(void);
    private:
        static std::string  field[FIELD_NUM];
        std::string         info[FIELD_NUM];
};

std::string Contact::field[11] = {
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

#endif