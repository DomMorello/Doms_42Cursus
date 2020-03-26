#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int main()
{
	int a = 0;
	int b = printf("%4.0d\n", a);
	return 0;
}