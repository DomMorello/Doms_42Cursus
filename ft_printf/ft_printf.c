#include "ft_printf.h"

// int	ft_printf(const char *format, ...)
// {
// 	va_list ap;


// }

int main()
{
	int a = 0;
	int b = 6;
	int c = 123456789;
	int d = -6;
	int e = -123456789;
	// printf("f: %hhd\n", -12); //9,223,372,036,854,775,807
	printf("a: %.0d\n", a);
	printf("a: %0d\n\n", a);
	printf("b: %5d\n", b);
	printf("b: %-0d\n\n", b);
	printf("c: %d\n", c);
	printf("c: %d\n\n", c);
	printf("d: %07d\n", d);
	printf("d: %d\n\n", d);
	printf("e: %.0d\n", e);
	printf("e: %d\n\n", e);	

	return 0;
}