#ifndef INTERN_HPP
#define INTERN_HPP

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern {
    public:
        Intern();
        Intern(const Intern & form);
        Intern& operator=(const Intern & form);
        ~Intern();

        Form* makeForm(const std::string &form, const std::string &target);

        class UnknownFormException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

#endif