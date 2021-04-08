#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    //������ ����
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

    //������ ���Ƽ� �������� ���ϴ� ���
    try
    {
        b1.signForm(f3);
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "------------" << std::endl;
    //������ ���Ƽ� ������ �� �ִ� ���
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