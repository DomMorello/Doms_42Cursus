#include "Convert.hpp"

Convert::Convert(std::string input, double val) : _input(input), _double(val) { }

Convert::Convert(const Convert & convert) {
    *this = convert;
}

Convert::~Convert() { }

Convert& Convert::operator=(const Convert & convert) {
    if (this == &convert)
        return *this;
    _input = convert.getInput();
    _double = convert.getDouble();
    return *this;
}

std::string Convert::getInput() const {
    return _input;
}

double Convert::getDouble() const {
    return _double;
}

void Convert::toChar() {
    std::cout << "char: ";
    int val;

    //int로 형변홤함으로써 만약 소수부분이 있다면 그 부분은 버려질 것이다.
    val = static_cast<int>(_double);
    //0 이 아니라면 소수부분이 있는 것이므로 char로 형변환 불가
    if (val - _double != 0)
        throw ConvertionException();
    // else if (std::isprint(static_cast<unsigned char>(val)))
    else if (val >= 32 && val <= 126)   //displayable하다면 출력
        std::cout << "'" << static_cast<char>(_double) << "'" << std::endl;
    else    //  출력가능하지 않으면 에러 발생
        throw NonDisplayableException();
}

void Convert::toInt() {
    std::cout << "int: ";
    long val;
    const char *str;

    str = _input.c_str();
    //nan이거나 inf인 경우 예외 발생
    if (std::isnan(_double) || std::isinf(_double))
        throw ConvertionException();
    //'a'처럼 char literal로 들어온 경우 처리
    if (_input.length() == 1 && std::isprint(static_cast<unsigned char>(str[0])))
        val = static_cast<long>(str[0]);
    else
        val = stol(_input);
    //long타입으로 변환한 값이 int범위를 넘어서면
    if (val > INT_MAX || val < INT_MIN)
        throw ConvertionException();
    std::cout << static_cast<int>(_double) << std::endl;
}

void Convert::toFloat() {
    std::cout << "float: ";
    int val;

    std::cout << static_cast<float>(_double);
    val = static_cast<int>(_double);
    //소수점이 있다면 끝에 f를 추가
    if (val - _double != 0)
        std::cout << "f" << std::endl;
    else    //소수가 없으면 뒤에 .0f 추가
        std::cout << ".0f" << std::endl;
}

void Convert::toDouble() {
    std::cout << "double: ";
    int val;

    // std::cout << _double;
    std::cout << static_cast<double>(_double);
    val = static_cast<int>(_double);
    //소수부분이 없으면 .0 을 추가
    if (val - _double == 0)
        std::cout << ".0";
    std::cout << std::endl;
}

const char* Convert::ConvertionException::what() const throw() {
    return "ConvertionException: impossible to convert";
}

const char* Convert::NonDisplayableException::what() const throw() {
    return "NonDisplayableException: impossible to display";
}