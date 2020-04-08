/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 17:30:55 by donglee           #+#    #+#             */
/*   Updated: 2020/04/08 17:31:36 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	size_t	i;

	result = (char *)s;
	i = 0;
	while (result[i])
		i++;
	while (result[i] != c)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	return (&result[i]);
}
