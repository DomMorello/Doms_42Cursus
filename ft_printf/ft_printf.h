#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

enum {MINUS, ZERO};

typedef struct	s_data
{
	char		*copy;
	int			flag[2];
	int			width;
	int			precision;
	char		type;
	va_list		ap;
	int			i;
	int			len;
}				t_data;

#endif