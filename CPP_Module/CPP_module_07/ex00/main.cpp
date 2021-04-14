#include "whatever.hpp"

class Awesome {
    public:
        Awesome( int n , std::string name) : _n( n ), _name( name ) { }

        bool operator==( Awesome const & rhs ) const {
            return (this->_n == rhs._n);
        }
        bool operator!=( Awesome const & rhs ) const{
            return (this->_n != rhs._n);
        }
        bool operator>( Awesome const & rhs ) const {
            return (this->_n > rhs._n);
        }
        bool operator<( Awesome const & rhs ) const {
            return (this->_n < rhs._n);
        }
        bool operator>=( Awesome const & rhs ) const {
            return (this->_n >= rhs._n);
        }
        bool operator<=( Awesome const & rhs ) const {
            return (this->_n <= rhs._n);
        }
        std::string getName() const {
            return (_name);
        }

        private:
            int _n;
            std::string _name;
};

int main( void ) {
    //int 테스트
    int a = 2;
    int b = 3;
    
    ::swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
    std::cout << "==============================" << std::endl;
    //string 테스트
    std::string c = "chaine1";
    std::string d = "chaine2";
    
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
    std::cout << "==============================" << std::endl;

    //같은 값이 들어오면 뒤에 들어온 인자를 리턴해야 한다.
    std::string e = "chaine3";
	std::string f = "chaine3";

	std::cout << "e = " << e << ", f = " << f << std::endl;
	::swap(e, f);
	std::cout << "e = " << e << ", f = " << f << std::endl;
	std::cout << "f -> " << &f  << std::endl;
	std::cout << "min(e, f) = " << ::min(e, f) << " (" << &::min(e, f) << ")" << std::endl;
	std::cout << "max(e, f) = " << ::max(e, f) << " (" << &::max(e, f) << ")" << std::endl;
    std::cout << "==============================" << std::endl;
    
    //객체 테스트
    Awesome awe1(2, "awe1");
    Awesome awe2(3, "awe2");
    
    ::swap( awe1, awe2 );
    std::cout << "awe1 = " << awe1.getName() << ", awe2 = " << awe2.getName() << std::endl;
    std::cout << "min( awe1, awe2 ) = " << ::min( awe1, awe2 ).getName() << std::endl;
    std::cout << "max( awe1, awe2 ) = " << ::max( awe1, awe2 ).getName() << std::endl;

    return 0;
}