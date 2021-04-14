#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <string>

template <typename T>
void print(const T &t) {
    std::cout << "element: " << t << std::endl;
}

template <typename T>
void iter(T *array, int len, void (*func)(const T &t)) {
    for (int i = 0; i < len; i++)
        func(array[i]);
}

#endif
