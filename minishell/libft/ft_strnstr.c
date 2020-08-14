/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 17:30:26 by donglee           #+#    #+#             */
/*   Updated: 2020/04/08 17:30:41 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*result;
	size_t	n_len;
	size_t	i;
	size_t	check;
	size_t	flag;

	result = (char *)haystack;
	i = 0;
	if ((n_len = ft_strlen(needle)) == 0)
		return (&result[i]);
	while (haystack[i] && i < len)
	{
		check = i;
		flag = 0;
		while (haystack[check] == needle[flag] && i + flag < len)
		{
			if (flag++ == n_len - 1)
				return (&result[i]);
			check++;
		}
		i++;
	}
	return (NULL);
}
