#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

enum {MINUS, ZERO};

typedef struct	s_data
{
	char		*copy;
	char		*print;
	int			flag[2];
	int			width;
	int			precision;
	char		type;
	va_list		ap;
	int			i;
	int			len;
}				t_data;

#endif