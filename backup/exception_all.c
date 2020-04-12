/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:33:40 by donglee           #+#    #+#             */
/*   Updated: 2020/04/09 21:36:41 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_exception1(char **format)
{
	while (!is_type(**format))
	{
		if (!is_valid(**format))
			return (ERROR);
		while (is_flag(**format))
			(*format)++;
		if (is_type(**format))
			break ;
		if (!is_valid(**format))
			return (ERROR);
		if (**format == '*')
		{
			(*format)++;
			if (is_type(**format))
				break ;
			if (ft_isdigit(**format) || !is_valid(**format))
				return (ERROR);
		}
		while (ft_isdigit(**format))
			(*format)++;
		break ;
	}
	return (TRUE);
}

int	handle_exception2(char **format)
{
	while (!is_type(**format))
	{
		if (is_flag(**format))
			return (ERROR);
		if (is_type(**format))
			break ;
		if (**format == '*' || !is_valid(**format))
			return (ERROR);
		if (**format == '.')
			(*format)++;
		if (is_type(**format))
			break ;
		break ;
	}
	return (TRUE);
}

int	handle_exception3(char **format)
{
	while (!is_type(**format))
	{
		if (**format == '.' || !is_valid(**format) || **format == '-')
			return (ERROR);
		if (**format == '*')
		{
			(*format)++;
			if (is_type(**format))
				break ;
			else
				return (ERROR);
		}
		else
		{
			while (ft_isdigit(**format))
				(*format)++;
			if (**format == '*' || is_flag(**format) || **format == '.')
				return (ERROR);
		}
		break ;
	}
	return (TRUE);
}

int	handle_exception4(char **format)
{
	while (!is_type(**format))
	{
		while (ft_isdigit(**format))
			(*format)++;
		if (is_type(**format))
			break ;
		break ;
	}
	return (TRUE);
}

int	exception_all(char *format)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (handle_exception1(&format) == ERROR)
				return (ERROR);
			if (handle_exception2(&format) == ERROR)
				return (ERROR);
			if (handle_exception3(&format) == ERROR)
				return (ERROR);
			if (handle_exception4(&format) == ERROR)
				return (ERROR);
		}
		format++;
	}
	return (TRUE);
}
