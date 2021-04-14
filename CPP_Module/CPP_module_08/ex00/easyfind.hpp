#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <deque>

template <typename T>
typename T::iterator easyfind(T &container, int n) {
	return (std::find(container.begin(), container.end(), n));
    //iterator 반환
    //다른 컨테이너 내부 함수들이 그런 식으로 구현돼있음
}

#endif