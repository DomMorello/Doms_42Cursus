#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main()
{
    //shrub 145 137
    //robot 72 45
    //presi 25 5
    Bureaucrat b1("donglee", 24);
    ShrubberyCreationForm shrub("shrub");
    
    b1.signForm(shrub); //24 > 145
    b1.executeForm(shrub);  //24 > 137

    std::cout << "----------------------" << std::endl;
    
    Bureaucrat b2("donglee", 43);
    RobotomyRequestForm robot("robot");
    
    // b2.signForm(robot); //43 > 72
    //b2가 sign을 하지 않고 execute하는 상황은 예외처리
    b2.executeForm(robot);  //43 > 45
    
    std::cout << "----------------------" << std::endl;

    Bureaucrat b3("donglee", 144);
    PresidentialPardonForm presi("presi");

    b3.signForm(presi); //144 < 25 불가능
    b3.executeForm(presi);  //144 < 5 불가능
}