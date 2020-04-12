/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 18:14:36 by donglee           #+#    #+#             */
/*   Updated: 2020/04/08 23:14:21 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_string;
	const unsigned char	*src_string;

	if (dst == NULL && src == NULL)
		return (NULL);
	src_string = src;
	dst_string = dst;
	while (n--)
		*(dst_string++) = *(src_string++);
	return (dst);
}
