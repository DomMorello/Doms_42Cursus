/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 18:14:18 by donglee           #+#    #+#             */
/*   Updated: 2020/04/07 18:14:25 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n-- && *(unsigned char *)s)
	{
		if (*(unsigned char *)s++ == (unsigned char)c)
			return ((void *)(s - 1));
	}
	return (NULL);
}
