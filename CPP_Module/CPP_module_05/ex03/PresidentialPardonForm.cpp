#include "./PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string & target)
    :
    Form("presi", 25, 5),
    _target(target)
    { }

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm & presi)
    :
    Form(presi),
    _target(presi._target)
    { }

PresidentialPardonForm::~PresidentialPardonForm() { }

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm & presi) {
    if (this == &presi)
        return *this;
    Form::operator=(presi);
    return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const {
    Form::execute(executor);

    std::cout << _target << " has been pardoned by Zafod Beeblebrox" << std::endl;
}