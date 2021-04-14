#include "Array.hpp"

int main()
{
    //기본 생성자 호출 가능
    Array<int> empty;

    //int test
    Array<int> arr1(10);
    for (size_t i = 0; i < 10; i++)
        arr1[i] = i;    //[] 연산자 오버라이딩 실행
    try
    {
        arr1[10] = 99;   //exception 발생! 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    //string test
    Array<std::string> arr2(5);
    arr2[0] = "hello";
    arr2[1] = "world";
    arr2[2] = "dong";
    arr2[3] = "lee";
    arr2[4] = "morello";

   for (size_t i = 0; i < arr2.size(); i++)
       std::cout << arr2[i] << std::endl;
    
    //없는 값에 접근하기 때문에 예외처리
    Array<char>	arr3(0);
	try
	{
		std::cout<<arr3[0];
	}
	catch(const std::exception& e)
	{
		std::cout<<e.what()<<'\n';
	}

    //const 객체에 접근가능
    Array<double> const arr4(3);
	for(int i=0; i<3 ; i++)
    {
        // arr4[i] = i; //const 타입이기 때문에 쓰기는 불가능
		std::cout<<arr4[i]<<' ';
    }
	std::cout<<'\n';
}