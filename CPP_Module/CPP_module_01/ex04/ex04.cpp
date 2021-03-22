#include <iostream>
#include <string>

int main(void)
{
    std::string str = "HI THIS IS BRAIN";
    std::string *str_p = &str;
    std::string &str_r = str;

    std::cout << *str_p << std::endl;
    std::cout << str_r << std::endl;
    return 0;
}