#include "./Bureaucrat.hpp"

int main()
{
    // Bureaucrat b1; //기본생성자 생성 불가
    Bureaucrat b2("donglee", 56);

    b2.incGrade();
    std::cout << b2;
    b2.decGrade();
    std::cout << b2;

    //복사생성자
    Bureaucrat b3(b2);
    std::cout << b3;

    //대입연산자 오버로딩
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

    //1등의 성적 올리기
    Bureaucrat fisrt("first", 1);
    try
    {
        fisrt.incGrade();
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }

    //꼴등의 성적 내리기
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