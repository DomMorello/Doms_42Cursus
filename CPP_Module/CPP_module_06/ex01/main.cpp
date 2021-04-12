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
    std::string alphanum = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *ret = new char[20];
    
    srand(clock());
    //랜덤한 숫자 혹은 알파벳을 문자열 ret 첫 8자리에 넣는다.
    for (size_t i = 0; i < 8; i++)
        ret[i] = alphanum.at(rand() % alphanum.length());
    std::cout << "ret first 8 bytes: " << std::string(ret, 8) << std::endl;
    //문자열 ret + 8 위치부터 4바이트만큼 int값을 랜덤하게 넣는다.
    *reinterpret_cast<int*>(ret + 8) = static_cast<int>(rand());
    std::cout << "ret next 4 bytes: " << *reinterpret_cast<int*>(ret + 8) << std::endl;
    //랜덤한 숫자 혹은 알파벳을 문자열 ret + 12 위치부터 8자리 넣는다.
    for (size_t i = 12; i < 20; i++)
        ret[i] = alphanum.at(rand() % alphanum.length());
    std::cout << "ret last 8 bytes: " << std::string(ret + 12, 8) << std::endl;
    return reinterpret_cast<void*>(ret);
}

Data* deserialize(void *raw) {
    Data *data = new Data;
    //void* 형을 char*으로 형변환
    char *tmp = reinterpret_cast<char*>(raw);
    
    //char* tmp 첫 8자리를 s1에 string으로 넣음
    data->s1 = std::string(tmp, 8);
    //int 4바이트만큼 tmp + 8 위치에 넣는다.
    data->n = *reinterpret_cast<int*>(tmp + 8);
    //tmp + 12 자리부터 8자리를 s2에 string으로 넣음
    data->s2 = std::string((tmp + 12), 8);
    return data;
}

int main()
{
    char *raw = reinterpret_cast<char*>(serialize());
    Data *deserial = reinterpret_cast<Data*>(deserialize(raw));

    std::cout << deserial->s1 <<std::endl;
    std::cout << deserial->n << std::endl;
    std::cout << deserial->s2 << std::endl;

    delete raw;
    delete deserial;
}