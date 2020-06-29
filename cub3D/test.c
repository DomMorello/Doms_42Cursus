#include <stdio.h>

void ff(int *a)
{
    *a++;
}

void f(int a, int b)
{
    static int aa = 0;
    static int bb = 0;

    if (a == 3)
        ff(&aa);
    if (b == 4)
        ff(&bb);
    printf("ret: %d %d\n", aa, bb);
}

int main(int argc, char const *argv[])
{
    int a = 3;
    int b = 4;
    f(a, b);
    f(a, b);
    return 0;
}
