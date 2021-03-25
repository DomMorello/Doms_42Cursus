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
    std::string line;   //getline 함수로 읽을 한 줄 문자열 (임시로 저장)
    std::size_t index;  //line 문자열 안에서 찾을 문자열(s1)의 첫번째 인덱스
    //인자는 4개만 와야함.
    if (argc != 4)
        return (print_err("Error: invalid input"));
    filepath = argv[1];
    s1 = argv[2];   //바뀌어야 하는 문자열
    s2 = argv[3];   //s1을 이 문자열로 바꿀 것임
    //빈 문자열이 하나라도 오면 에러 처리
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
        //한 문자열 line 안에서 s1문자열 찾아서 s2로 바꿔주는 반복문
        while (true)
        {
            index = line.find(s1, index);
            if (index == std::string::npos) //s1 문자열을 못찾았을 경우 반복문 나옴
                break ;
            line.replace(index, s1.length(), s2);   //s1문자열을 s2로 바꿈
            index += s2.length();
            //여기서 index를 증가해줘야 반복문 첫째줄로 가서 그 다음부터 find를 한다.
        }
        writeFile << line;  //replace된 line한 줄을 씀. s1 문자열을 못찾으면 그대로 씀.
        if (!readFile.eof())
            writeFile << std::endl; //file의 끝까지 다 읽었으면 개행 추가
    }
    readFile.close();
    writeFile.close();
    return (0);
}