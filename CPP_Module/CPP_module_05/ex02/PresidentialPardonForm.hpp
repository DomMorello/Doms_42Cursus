#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "Form.hpp"

class PresidentialPardonForm : public Form {
    private:
        PresidentialPardonForm();

    public:
        PresidentialPardonForm(const PresidentialPardonForm & presi);
        ~PresidentialPardonForm();
        PresidentialPardonForm& operator=(const PresidentialPardonForm & shrub);

};

#endif