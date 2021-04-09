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

//순수가상함수이지만 여기서 몸체를 구현해도 된다. 단 자식 클래스에서 무조건 오버라이딩을 해야 한다. 
void Form::execute(Bureaucrat const & executor) const {
    //form에 사인할 성적이 되지 않으면 예외처리
    if (_gradeToSign < executor.getGrade())
        throw GradeTooLowException();
    //form에 사인돼있지 않으면 예외처리
    if (_signed == false)
        throw NotSignedException(); //예외처리를 위해 직접 만들어준 클래스
}

const char* Form::GradeTooHighException::what() const throw() {
    return "Grade Too High Exception: grade is too high";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Grade Too Low Exception: grade is too low";
}

//sign돼있지 않은 경우를 예외처리하기 위해 오버라이딩한 what함수
const char* Form::NotSignedException::what() const throw() {
    return "Not Signed Exception: form is not signed";
}

std::ostream& operator<<(std::ostream& os, const Form & form) {
    return (os << form.getName() << ", Form signed "
            << std::boolalpha << form.getSigned()
            << ", gradeToSige " << form.getGradeToSign()
            << ", gradeToExec " << form.getGradeToExec() << std::endl);
}