#include <iostream>
#include <string>
#include <ctime>

struct Data
{
    std::string s1;
    int         n;
    std::string s2;
};

void serialize(void) {
    const char alphanum[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    std::string s1("");
    std::string s2("");
    int randInt;

    srand(clock());
    randInt = rand();
    for (size_t i = 0; i < 8; i++)
    {
        s1 += alphanum[rand() % (strlen(alphanum) - 1)];
        s2 += alphanum[rand() % (strlen(alphanum) - 1)];
    }
}

// Data* deserialize(void *raw) {
    
// }

int main()
{
    serialize();
}