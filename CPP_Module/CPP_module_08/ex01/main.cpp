#include "span.hpp"

//container 전체 출력
template <typename T>
void print(T & container) {
    for (typename T::iterator i = container.begin(); i != container.end(); i++)
        std::cout << *i << std::endl;
}

int main()
{
    Span sp = Span(5);
    
    //사이즈에 대한 에러 확인
    try
    {
        sp.addNumber(5);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        // sp.addNumber(18);    //5개인데 더 추가하면 예외발생

        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "----------------------" << std::endl;
    //size가 1인 경우 간격구하면 에러처리
    Span sp1 = Span(1);
    try
    {
        sp1.addNumber(15);

        sp1.shortestSpan();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "----------------------" << std::endl;
    // 정상적으로 가장 짧은 간격과 가장 넓은 간격을 구하는 테스트
    std::vector<int>	vec;
	Span sp2(10000);

    try
    {
        for(int i=0; i<10000; i++)
            vec.push_back(i*3);  // 0부터 29997이 들어감
        //반복자를 이용해서 한 번에 10000개를 add할 수 있음.
        //이 과정에서 10001개를 넣으려고 하면 예외 발생함.
        sp2.addNumber(vec.begin(), vec.end());

        std::cout << sp2.shortestSpan() << std::endl;
        // 3의 배수에서 가장 적은 차이는 3.
        std::cout << sp2.longestSpan() << std::endl;
        // 가장 넓은 차이는 0과 29997 이므로 29997
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}