#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "Form.hpp"
#include <cstdlib>

class PresidentialPardonForm : public Form {
    private:
        const std::string _target;
        PresidentialPardonForm();

    public:
        PresidentialPardonForm(const std::string & target);
        PresidentialPardonForm(const PresidentialPardonForm & presi);
        ~PresidentialPardonForm();
        PresidentialPardonForm& operator=(const PresidentialPardonForm & presi);

        void execute(Bureaucrat const & executor) const;
};

#endif