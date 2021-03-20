#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include "./Contact.hpp"

class Directory {
    public:
        Directory(void);
        void addContact(void);
        void searchContact(void);

    private:
        int idx;
        Contact contacts[SIZE];
};

#endif