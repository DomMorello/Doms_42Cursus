#include <stdio.h>


typedef struct  s_test
{
    int a;
    int b;
    int c;
}               t_test;

int main(int argc, char const *argv[])
{
    t_test test;
    fun1(&test);
    printf("test a: %d, b: %d c: %d\n", test.a, test.b, test.c);
    return 0;
}
