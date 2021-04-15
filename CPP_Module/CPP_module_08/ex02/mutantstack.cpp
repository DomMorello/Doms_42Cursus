#include "mutantstack.hpp"

template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>() { }

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> & stack) : std::stack<T>(stack) { }

template <typename T>
MutantStack<T>::~MutantStack() { }

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack<T> & stack) {
    //stack ���ο� protected�� c ������ �ִµ�
    //�̰� stack ������ container�� ����Ų��.
    this->c = stack.c;
    return *this;
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin(void) {
    return this->c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end(void) {
    return this->c.end();
}