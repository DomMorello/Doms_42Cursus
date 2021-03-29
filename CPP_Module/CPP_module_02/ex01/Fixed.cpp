#include "./Fixed.hpp"

Fixed::Fixed() : value(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int val) {
    value = val << bits;
    //맨 오른 쪽 8비트는 소수부분을 담아야 하기 때문에
    //정수는 정수부분으로 왼 쪽으로 8칸 옮겨줘야 정수부분에 위치한다.
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float val) {
    value = roundf(val * (1 << bits));  //부동소수점으로 변환
    std::cout << "Float constructor called" << std::endl;
} 

Fixed::Fixed(const Fixed& fixed) {
    std::cout << "Copy constructor called" << std::endl;
    *this = fixed;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& fixed) {
    std::cout << "Assignation operator called" << std::endl;
    value = fixed.getRawBits();
    return *this;
}

int     Fixed::getRawBits(void) const {
    return value;
}

void    Fixed::setRawBits(int const raw) {
    value = raw;
}

float   Fixed::toFloat(void) const {
    return (float)value / (1 << bits);
}

int     Fixed::toInt(void) const {
    //Int 생성자에서 고정소수점으로 바꾼 것을 다시 정수로 바꾸려면
    //왼쪽으로 8번 옮겼던 것을 다시 오른쪽으로 8번 되돌려준다.
    return value >> bits;
}

std::ostream& operator<<(std::ostream& output, const Fixed& fixed) {
    return output << fixed.toFloat();
}