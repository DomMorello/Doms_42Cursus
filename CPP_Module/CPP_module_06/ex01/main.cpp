#include <iostream>
#include <string>
#include <ctime>
#include <string.h>

struct Data
{
    std::string s1;
    int         n;
    std::string s2;
};

void *serialize(void) {
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
    char *ret = new char[sizeof(s1) + sizeof(randInt) + sizeof(s2)];
    std::cout << "s1 : " << s1 << std::endl;
    std::cout << "n : " << randInt << std::endl;
    std::cout << "s2 : " << s2 << std::endl;

    memcpy(ret, &s1, sizeof(s1));
    memcpy(ret + sizeof(s1), &randInt, sizeof(randInt));
    memcpy(ret + sizeof(s1), &s2, sizeof(s2));
    return ret;
}

Data* deserialize(void *raw) {
    Data *data = new Data;

    data->s1 = reinterpret_cast<char*>(raw);
    data->n = *reinterpret_cast<int*>(reinterpret_cast<char*>(raw) + sizeof(data->s1));
    data->s2 = reinterpret_cast<char*>(raw) + sizeof(data->s1) + sizeof(data->s2);
    return data;
}

int main()
{
    char *serial = reinterpret_cast<char*>(serialize());
    Data *deserial = deserialize(serial);

    std::cout << deserial->s1 << std::endl;
    std::cout << deserial->n << std::endl;
    std::cout << deserial->s2 << std::endl;  
}