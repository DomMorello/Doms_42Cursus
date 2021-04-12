#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

class Convert {
    private:
        std::string _input;
        double _double;
        Convert();
    public:
        Convert(std::string input, double val);
        Convert(const Convert & convert);
        ~Convert();
        Convert& operator=(const Convert & convert);

        std::string getInput() const;
        double getDouble() const;
        void toChar();
        void toInt();
        void toFloat();
        void toDouble();

        class ConvertionException : public std::exception {
            public:
                virtual const char* what() const throw();
        };

        class NonDisplayableException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

#endif