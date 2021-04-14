#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <vector>

typedef std::vector<int>::iterator itr;

class Span {
    private:
        std::vector<int> _ints;
        unsigned int _size;
        Span();
    public:
        Span(unsigned int n);
        Span(const Span & span);
        Span& operator=(const Span & span);
        ~Span();

        void addNumber(int num);
        void addNumber(itr const &begin, itr const &end);
        unsigned int shortestSpan(void) const;
        unsigned int longestSpan(void) const;

        class FullException : public std::exception {
            public:
                virtual const char* what() const throw() ;
        };
        class NotFoundException : public std::exception {
            public:
                virtual const char* what() const throw() ;
        };
};

#endif
