/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 18:13:55 by donglee           #+#    #+#             */
/*   Updated: 2020/04/07 18:14:05 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *dst_string;
	unsigned char *src_string;

	dst_string = (unsigned char *)dst;
	src_string = (unsigned char *)src;
	while (n--)
	{
		*dst_string = *src_string;
		if (*src_string == (unsigned char)c)
			return ((void *)dst_string + 1);
		dst_string++;
		src_string++;
	}
	return (NULL);
}
