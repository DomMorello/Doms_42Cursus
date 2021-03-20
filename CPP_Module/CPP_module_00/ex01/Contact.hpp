#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>

class Contact {
public:
	Contact() {
		index = idCounter++;
	}
	static int idCounter;
private:
    enum Info
    {
        FIRST_NAME,
        LAST_NAME,
        NICKNAME,
        LOGIN,
        POSTAL,
        EMAIL,
        PHONE,
        BIRTHDAY,
        FAV_MEAL,
        UNDERWEAR,
        SECRET
    };
	std::string info[11];
	int index;
};

int Contact::idCounter = 1;

#endif