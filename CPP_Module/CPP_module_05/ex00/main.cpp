#include "./Bureaucrat.hpp"

int main()
{
    // Bureaucrat b1; //�⺻������ ���� �Ұ�
    Bureaucrat b2("donglee", 56);

    b2.incGrade();
    std::cout << b2;
    b2.decGrade();
    std::cout << b2;

    //���������
    Bureaucrat b3(b2);
    std::cout << b3;

    //���Կ����� �����ε�
    Bureaucrat b4 = b3;
    std::cout << b4;

    //Too low
    try
    {
        Bureaucrat error1("err1", -12);
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }

    //Too high
    try
    {
        Bureaucrat error2("err2", 151);
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }

    //1���� ���� �ø���
    Bureaucrat fisrt("first", 1);
    try
    {
        fisrt.incGrade();
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }

    //�õ��� ���� ������
    Bureaucrat last("last", 150);
    try
    {
        last.decGrade();
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}