#include "ft_printf.h"

int main()
{
    int a = 3;
    unsigned int b = 123;
    char *c = "abc";
    char d = 'd';
    unsigned int e = 543;
    ft_printf("%d %u %s %c %x %% \n", a,b,c,d,e);
    return 0;
}