#include <iostream>
#include <string>
#include <locale>

int main(int argc, char *argv[])
{
    if (!argv[1])
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    else
    {
        for (int i = 1; i < argc; i++)
        {
            std::string str(argv[i]);
            for (int j = 0; j < (int)str.length(); j++)
                std::cout << (char)std::toupper(str[j]);
        }
        std::cout << std::endl;
    }
    return (0);
}