#include "./Fixed.hpp"

Fixed::Fixed() : value(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int val) {
    value = val << bits;    //val * 2^8(bits)
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float val) {
    value = roundf(val * (1 << bits));
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
    return value >> bits;
}

std::ostream& operator<<(std::ostream& output, const Fixed& fixed) {
    return output << fixed.toFloat();
}