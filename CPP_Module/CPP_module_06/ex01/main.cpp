#include <iostream>
#include <string>
#include <ctime>

struct Data
{
    std::string s1;
    int         n;
    std::string s2;
};

void *serialize(void) {
    std::string alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEGFHIJKLMNOPQRSTUVWXYZ";
	std::string s1("");
	std::string s2("");
	int n;
    //52 bytes
	char *ret = new char[sizeof(s1) + sizeof(int) + sizeof(s2)];
    
    srand(clock());
    for (size_t i = 0; i < 8; i++)
	{
		s1 += alphanum[rand() % alphanum.length()];
		s2 += alphanum[rand() % alphanum.length()];
	}
	n = rand();

    //copy bytes
	memcpy(ret, &s1, sizeof(s1));
	memcpy(ret + sizeof(s1), &n, sizeof(n));
	memcpy(ret + sizeof(s1) + sizeof(n), &s2, sizeof(s2));

    return reinterpret_cast<void*>(ret);
}

Data* deserialize(void *raw) {
    Data *data = new Data;
    
	data->s1 = reinterpret_cast<char*>(raw);
	data->n = *reinterpret_cast<int*>(reinterpret_cast<char*>(raw) + sizeof(data->s1));
	data->s2 = reinterpret_cast<char*>(reinterpret_cast<char*>(raw) + sizeof(data->s1) + sizeof(data->n));
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
