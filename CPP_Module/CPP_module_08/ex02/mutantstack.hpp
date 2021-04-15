#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <stack>
#include <deque>

template <typename T>
class MutantStack : public std::stack<T> {
    public:
        MutantStack();
        MutantStack(const MutantStack<T> & stack);
        ~MutantStack();
        MutantStack<T>& operator=(const MutantStack<T> & stack);

        //container_type ¿∫ second template parameter (container) ¿Ã¥Ÿ.
        typedef typename std::stack<T>::container_type::iterator iterator;
        iterator begin(void);
        iterator end(void);
};

#endif