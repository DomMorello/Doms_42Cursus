#include "Intern.hpp"

int main()
{
    Intern i1;

    Bureaucrat b1("donglee", 1);

    //makeForm 정상 작동하는 경우
    Form* f1 = i1.makeForm("shrubbery creation", "shrub");
    b1.signForm(*f1);
    b1.executeForm(*f1);
    
    delete f1;
    std::cout << "-------------------" << std::endl;

    //form 이 존재하지 않는 것을 넣었을 때 예외처리
    Intern i2;
    try
    {
        i2.makeForm("unknown", "shrub");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}