#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    //생성자 오류
    try
    {
        Form f1("error1", 0, 130);
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "------------" << std::endl;
    try
    {
        Form f2("error2", 4, 160);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "------------" << std::endl;
    Bureaucrat b1("donglee", 130);
    Bureaucrat b2("morello", 12);
    Form f3("secondClass", 50, 30);

    //성적이 낮아서 사인하지 못하는 경우
    try
    {
        b1.signForm(f3);
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "------------" << std::endl;
    //성적이 높아서 사인할 수 있는 경우
    try
    {
        b2.signForm(f3);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "------------" << std::endl;
}