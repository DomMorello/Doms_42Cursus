#include "iter.hpp"

class Awesome {
    public:
        Awesome( void ) : _n( 42 ) { return; }
        int get( void ) const { return this->_n; }
    private:
        int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

template< typename T >
void print2( T const & x ) {
    std::cout << x << std::endl;
    return;
}

int main()
{
    //int test
    int arr1[3] = {1, 3, 5};
    iter(arr1, 3, print);

    //string test
    std::string arr2[3] = {"hello", "world", "donglee"};
    iter(arr2, 3, print);

    //객체 test
    Awesome tab[5];
    iter(tab, 5, print2);
}