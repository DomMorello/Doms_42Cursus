#include "ft_printf.h"

// int	ft_printf(const char *format, ...)
// {
// 	va_list ap;


// }

int main()
{
	// int a = 48;
	// printf("%-s\n","abc");
	char a = 'a';
	// char *s = "abc";
	void *s = &a;
	printf("%-20p\n", s);
	printf("%20p\n", s);
	return 0;
}