#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include "Contact.hpp"

class Directory {
public:
    void addContact(void);
    void searchContact(void);
private:
    Contact contacts[8];
};

#endif 