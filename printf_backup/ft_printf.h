/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:37:41 by donglee           #+#    #+#             */
/*   Updated: 2020/04/09 21:38:25 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

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
	va_list		ap_copy;
	int			i;
	int			len;
}				t_data;

/* this part must be deleted after making makefile */
int			ft_get_digits(long long nbr);
int ft_isdigit(int c);
char		*ft_putnbr_base(unsigned long nbr, char *base);
void 		ft_putnbrl_fd(long long n, int fd);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t ft_strlen(const char *s);


void		data_init(t_data *data);
int			is_type(char c);
int 		is_flag(char c);
int			is_valid(char c);
void		input_flag(t_data *data, char **ptr);
void		input_width(t_data *data, char **ptr, va_list *list);
void		input_precision(t_data *data, char **ptr, va_list *list);
void		input_type(t_data *data, char **ptr);
void		input_data(t_data *data, char **ptr, va_list *list);
int			handle_exception1(char **format);
int			handle_exception2(char **format);
int 		handle_exception3(char **format);
int			handle_exception4(char **format);
int 		exception_all(char *format);
int			exception_data(t_data *data, const char *format);
int			print_c(t_data *data);
void 		prints_from_head(t_data *data, char *s, int gap);
void		prints_from_tail(t_data *data, char *s, int gap);
void		print_s(t_data *data);
void		printp_from_haed(t_data *data, char *convert, int gap, int len);
void		printp_from_tail(t_data *data, char *convert, int gap, int len);
void		printp_body(t_data *data, char *convert, int len);
int			print_p(t_data *data);
void		printd_gap(t_data *data, long long ret, int len);
void		printd_zero(t_data *data, int len, int *ret);
void		printd_nbr(t_data *data, long long ret, int len);
void		printd_body(t_data *data, int ret, int len);
void		printu_body(t_data *data, unsigned int ret, int len);
void		print_di(t_data *data);
void		print_u(t_data *data);
void		printx_body(t_data *data, unsigned int ret, char *convert, int len);
void 		print_x_all(t_data *data, unsigned int ret, char *convert, int len);
int			print_x(t_data *data);
void		print_per_head(t_data *data);
void		print_per(t_data *data);
int			print_data(t_data *data);
int			modify_ds_data(t_data *data, char *cpy);
int			modify_p_data(t_data *data, char *cpy);
int			modify_data(t_data *data, char *cpy);
int			move_to_print(t_data *data);
int			parse_data(t_data *data, const char *format);
int			ft_printf(const char *format, ...);

#endif
