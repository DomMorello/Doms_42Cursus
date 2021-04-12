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
    //������ ���� Ȥ�� ���ĺ��� ���ڿ� ret ù 8�ڸ��� �ִ´�.
    for (size_t i = 0; i < 8; i++)
        ret[i] = alphanum.at(rand() % alphanum.length());
    std::cout << "ret first 8 bytes: " << std::string(ret, 8) << std::endl;
    //���ڿ� ret + 8 ��ġ���� 4����Ʈ��ŭ int���� �����ϰ� �ִ´�.
    *reinterpret_cast<int*>(ret + 8) = static_cast<int>(rand());
    std::cout << "ret next 4 bytes: " << *reinterpret_cast<int*>(ret + 8) << std::endl;
    //������ ���� Ȥ�� ���ĺ��� ���ڿ� ret + 12 ��ġ���� 8�ڸ� �ִ´�.
    for (size_t i = 12; i < 20; i++)
        ret[i] = alphanum.at(rand() % alphanum.length());
    std::cout << "ret last 8 bytes: " << std::string(ret + 12, 8) << std::endl;
    return reinterpret_cast<void*>(ret);
}

Data* deserialize(void *raw) {
    Data *data = new Data;
    //void* ���� char*���� ����ȯ
    char *tmp = reinterpret_cast<char*>(raw);
    
    //char* tmp ù 8�ڸ��� s1�� string���� ����
    data->s1 = std::string(tmp, 8);
    //int 4����Ʈ��ŭ tmp + 8 ��ġ�� �ִ´�.
    data->n = *reinterpret_cast<int*>(tmp + 8);
    //tmp + 12 �ڸ����� 8�ڸ��� s2�� string���� ����
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