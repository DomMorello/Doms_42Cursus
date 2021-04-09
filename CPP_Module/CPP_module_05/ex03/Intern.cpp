#include "./Intern.hpp"

Intern::Intern() { }

Intern::Intern(const Intern & form) {
    *this = form;
}

Intern& Intern::operator=(const Intern & form) {
    (void)form;
    return *this;
}

Intern::~Intern() { }

Form* Intern::makeForm(const std::string &form, const std::string &target) {
    std::string targets[3] = 
    {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    Form* forms[3];
    forms[0] = new ShrubberyCreationForm(target);
    forms[1] = new RobotomyRequestForm(target);
    forms[2] = new PresidentialPardonForm(target);
    
    Form* ret = NULL;
    for (int i = 0; i < 3; i++)
    {
        if (targets[i] == form)
        {
            std::cout << "Intern creates " << form << std::endl;
            ret = forms[i];
            continue ;
        }
        //일치하는 form을 제외하고는 전부 메모리 해제함.
        delete forms[i];
    }
    //일치하는 form이 없을 경우 예외를 던짐
    if (!ret)
        throw UnknownFormException();
    return ret;
}

const char* Intern::UnknownFormException::what() const throw() {
    return "UnknownFormException: there is no matching form"; 
}