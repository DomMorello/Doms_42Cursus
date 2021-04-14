#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>

template <typename T>
class Array {
    private:
        T *_arr;
        unsigned int _size;
    public:
        Array() : _arr(NULL), _size(0) { }

        Array(unsigned int n) {
            _arr = new T[n];
            _size = n;
        }

        Array(const Array& array) {
            *this = array;
        }

        //깊은 복사를 한다
        Array& operator=(const Array& arr) {
            if (this == &arr)
                return *this;
            _size = arr.size();
            _arr = new T[_size];
            for (size_t i = 0; i < _size; i++)
                _arr[i] = arr._arr[i];
            return *this;
        }

        ~Array() {
            if (_arr)
                delete[] _arr;
        }

        //const 타입값은 읽을 수만 있게 하기 위해서 추가적으로 만듦
        const T& operator[](unsigned int idx) const {
            if (idx < 0 || idx >= _size)
                throw std::exception();
            return _arr[idx];
        }

        //읽기, 쓰기 둘 다 가능
        T& operator[](unsigned int idx) {
            if (idx < 0 || idx >= _size)
                throw std::exception();
            return _arr[idx];
        }

        unsigned int size() const { return _size; }
};

#endif