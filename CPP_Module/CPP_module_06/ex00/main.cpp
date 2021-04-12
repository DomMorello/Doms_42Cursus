#include "Convert.hpp"

int main(int argc, const char *argv[])
{
    double input;

    if (argc != 2)
    {
        std::cout << "Error: Invalid argument" << std::endl;
        return -1;
    }
    //'a'처럼 출력가능한 char literal로 들어온 경우 처리
    std::string str = argv[1];
    if (str.length() == 1 && std::isprint(static_cast<unsigned char>(argv[1][0])))
    {
        input = static_cast<double>(argv[1][0]);
    }
    else
    {
        try
        {
            //문자열을 double로 변환
            input = std::stod(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Invalid Argument" << std::endl;
            return 0;
        }
    }
    Convert C(argv[1], input);
    
    //char
    try
    {
        C.toChar();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    //int
    try
    {
        C.toInt();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    //float
    try
    {
        C.toFloat();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    //double
    try
    {
        C.toDouble();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}