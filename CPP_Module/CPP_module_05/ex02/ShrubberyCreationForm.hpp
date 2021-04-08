#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "Form.hpp"

class ShrubberyCreationForm : public Form {
    private:
        const std::string _target;
        ShrubberyCreationForm();

    public:
        ShrubberyCreationForm(const std::string & _type);
        ShrubberyCreationForm(const ShrubberyCreationForm & shrub);
        ~ShrubberyCreationForm();
        ShrubberyCreationForm& operator=(const ShrubberyCreationForm & shrub);

};

#endif