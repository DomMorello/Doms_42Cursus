#include "./Bureaucrat.hpp"

Bureaucrat::Bureaucrat(const std::string &name, int grade) :_name(name), _grade(grade) {
    if (_grade < 1)
        throw GradeTooHighException();
    if (_grade > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat & b) : _name(b.getName()), _grade(b.getGrade()) {
    *this = b;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat & b) {
    //자기 자신이 들어오면 자기 자신 반환
    if (this == &b)
        return *this;
    _grade = b.getGrade();
    if (_grade < 1)
        throw GradeTooHighException();
    if (_grade > 150)
        throw GradeTooLowException();
    return *this;
}

Bureaucrat::~Bureaucrat() { }

const std::string Bureaucrat::getName() const {
    return _name;
}

int Bureaucrat::getGrade() const {
    return _grade;
}

void Bureaucrat::incGrade() {
    if (_grade == 1)
        throw GradeTooHighException();
    _grade--;
}

void Bureaucrat::decGrade() {
    if (_grade == 150)
        throw GradeTooLowException();
    _grade++;
}

void Bureaucrat::signForm(Form & form) {
    try
    {
        form.beSigned(*this);
        std::cout << _name << " signs " << form.getName() << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << _name << " cannot sign " << form.getName() << " because ";
        std::cerr << e.what() << std::endl;
    }
}

//함수 선언부에는 Bureaucrat:: 을 추가해줘야 인식한다.
const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "GradeTooHighException: grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "GradeTooLowException: grade is too low";
}

std::ostream& operator<<(std::ostream &os, const Bureaucrat &b) {
    return (os << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl);
}