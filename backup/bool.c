/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:32:09 by donglee           #+#    #+#             */
/*   Updated: 2020/04/09 21:32:47 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' ||
		c == 'd' || c == 'i' || c == 'u' ||
		c == 'x' || c == 'X' || c == '%')
		return (TRUE);
	return (FALSE);
}

int	is_flag(char c)
{
	if (c == '-' || c == '0')
		return (TRUE);
	return (FALSE);
}

int	is_valid(char c)
{
	if (ft_isdigit(c) || is_flag(c) || c == '.' || c == '*')
		return (TRUE);
	return (FALSE);
}
