#include "span.hpp"

Span::Span(unsigned int n) : _size(n) { }

Span::Span(const Span & span) {
    *this = span;
}

Span& Span::operator=(const Span & span) {
    if (this == &span)
        return *this;
    _ints = span._ints;
    _size = span._size;
    return *this;
}

Span::~Span() { }

void Span::addNumber(int num) {
    //현재 꽉차있으면 예외
    if (_ints.size() == _size)
        throw FullException();
    _ints.push_back(num);
}

void Span::addNumber(itr const &begin, itr const &end) {
    //여러개를 추가하는데 여러개를 더한 값이 _size를 넘어버리면 넘치니까 예외
    if (_ints.size() + std::distance(begin, end) > _size)
        throw FullException();
    itr start = begin;
    while (start != end)
    {
        _ints.push_back(*start);
        start++;
    }
}

unsigned int Span::shortestSpan() const {
    //벡터가 비어있거나 사이즈가 1이면 예외처리
    if (_ints.empty() || _ints.size() == 1)
        throw NotFoundException();
    std::vector<int> tmp = _ints;
    std::sort(tmp.begin(), tmp.end()); //오름차순 정렬

    std::vector<int> span(_size);   //정렬된 숫자의 간격들을 저장하기 위한 벡터
    //오름차순 된 벡터의 원소들의 간격들을 span벡터에 저장한다.
    std::adjacent_difference(tmp.begin(), tmp.end(), span.begin());
    //간격들이 저장된 벡터를 다시 오름차순으로 정렬하면 가장 처음 원소가 가장 적은 간격임.
    std::sort(span.begin() + 1, span.end());
    //span[0]에는 begin[0]의 값이 저장됨(원래 함수가 그렇게 작동함)
    return span[1];
}

unsigned int Span::longestSpan() const {
    //벡터가 비어있거나 사이즈가 1이면 예외처리
    if (_ints.empty() || _ints.size() == 1)
        throw NotFoundException();
    std::vector<int> tmp = _ints;
    std::sort(tmp.begin(), tmp.end());
    //오름차순으로 정렬한 후에 마지막 원소에서 처음 원소를 뺴면 가장 큰 간격
    return tmp.back() - tmp.front();
    //back과 front는 원소의 참조값을 반환하기 때문에 여기서는 int값이다.
}

const char* Span::FullException::what() const throw() {
    return "FullException: is full";
}

const char* Span::NotFoundException::what() const throw() {
    return "NotFoundException: cannot find the span";
}