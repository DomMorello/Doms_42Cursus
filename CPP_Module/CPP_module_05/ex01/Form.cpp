#include "./Form.hpp"

Form::Form(std::string name, int gradeToSign, int gradeToExec)
    :
    _name(name),
    _signed(false),
    _gradeToSign(gradeToSign),
    _gradeToExec(gradeToExec)
{
    if (_gradeToSign < 1 || _gradeToExec < 1)
        throw GradeTooHighException();
    if (_gradeToSign > 150 || _gradeToExec > 150)
        throw GradeTooLowException();
}

Form::Form(const Form & form)
    :
    _name(form.getName()),
    _signed(form.getSigned()),
    _gradeToSign(form.getGradeToSign()),
    _gradeToExec(form.getGradeToExec())    
{
    *this = form;
}

Form& Form::operator=(const Form & form) {
    if (this == &form)
        return *this;
    _signed = form.getSigned();
    if (form.getGradeToSign() < 1 || form.getGradeToExec() < 1)
        throw GradeTooHighException();
    if (form.getGradeToExec() > 150 || form.getGradeToExec() > 150)
        throw GradeTooLowException();
    return *this;
}

Form::~Form() { }

const std::string Form::getName() const {
    return _name;
}

bool Form::getSigned() const {
    return _signed;
}

int Form::getGradeToSign() const {
    return _gradeToSign;
}

int Form::getGradeToExec() const {
    return _gradeToExec;
}

void Form::beSigned(const Bureaucrat & b) {
    if (_gradeToSign > b.getGrade())
        _signed = true;
    else
        throw Form::GradeTooLowException();
}

const char* Form::GradeTooHighException::what() const throw() {
    return "Grade Too High Exception: grade is too high";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Grade Too Low Exception: grade is too low";
}

std::ostream& operator<<(std::ostream& os, const Form & form) {
    return (os << form.getName() << ", Form signed "
            << std::boolalpha << form.getSigned()
            << ", gradeToSige " << form.getGradeToSign()
            << ", gradeToExec " << form.getGradeToExec());
}