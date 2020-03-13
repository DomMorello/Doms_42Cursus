#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list ap;


}

int main()
{
	int a = 123;
	int b = -123;
	double c = 1.23456;

	printf("%5.2f\n", c);
	printf("%5.34f\n", c);
	return 0;
}