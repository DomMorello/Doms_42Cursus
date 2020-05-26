#include <stdio.h>
#include "./main.h"
#define _USE_MATH_DEFINES
#include <math.h>

int main(int argc, char const *argv[])
{
    double a = 66.0;
    double b = 180.0;
    double c = 1.0;
    double d = 2.0;

    printf("%f \n", d * atan(0.66 / 1.0));
    printf("radian 66 = %f\n", a * M_PI / b);
    return 0;
}
