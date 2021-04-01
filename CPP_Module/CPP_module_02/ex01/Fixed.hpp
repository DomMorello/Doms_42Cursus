#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed{
    public:
        Fixed();
        Fixed(const int val);
        Fixed(const float val);
        Fixed(const Fixed& fixed);
        ~Fixed();
        Fixed& operator=(const Fixed& fixed);
        int getRawBits(void) const;
        void setRawBits(int const raw);
        float toFloat(void) const;
        int toInt(void) const;

    private:
        int value;
        static const int bits = 8;
};

std::ostream& operator<<(std::ostream& output, const Fixed& fixed);

#endif