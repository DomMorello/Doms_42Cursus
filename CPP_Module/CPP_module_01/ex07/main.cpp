#include <iostream>
#include <string>
#include <fstream>

int print_err(std::string err) {
    std::cout << err << std::endl;
    return (-1);
}

int main(int argc, char *argv[])
{
    std::string s1;
    std::string s2;
    std::string filepath;
    std::ifstream readFile;
    std::ofstream writeFile;
    std::string line;   //getline �Լ��� ���� �� �� ���ڿ� (�ӽ÷� ����)
    std::size_t index;  //line ���ڿ� �ȿ��� ã�� ���ڿ�(s1)�� ù��° �ε���
    //���ڴ� 4���� �;���.
    if (argc != 4)
        return (print_err("Error: invalid input"));
    filepath = argv[1];
    s1 = argv[2];   //�ٲ��� �ϴ� ���ڿ�
    s2 = argv[3];   //s1�� �� ���ڿ��� �ٲ� ����
    //�� ���ڿ��� �ϳ��� ���� ���� ó��
    if (s1.empty() || s1.empty())
        return (print_err("Error: strings are empty"));
    
    readFile.open(filepath);
    filepath += ".replace";
    writeFile.open(filepath);
    if (!readFile.is_open() || !writeFile.is_open())
        return (print_err("Error: open failure"));
    while (getline(readFile, line))
    {
        index = 0;
        //�� ���ڿ� line �ȿ��� s1���ڿ� ã�Ƽ� s2�� �ٲ��ִ� �ݺ���
        while (true)
        {
            index = line.find(s1, index);
            if (index == std::string::npos) //s1 ���ڿ��� ��ã���� ��� �ݺ��� ����
                break ;
            line.replace(index, s1.length(), s2);   //s1���ڿ��� s2�� �ٲ�
            index += s2.length();
            //���⼭ index�� ��������� �ݺ��� ù°�ٷ� ���� �� �������� find�� �Ѵ�.
        }
        writeFile << line;  //replace�� line�� ���� ��. s1 ���ڿ��� ��ã���� �״�� ��.
        if (!readFile.eof())
            writeFile << std::endl; //file�� ������ �� �о����� ���� �߰�
    }
    readFile.close();
    writeFile.close();
    return (0);
}