/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 17:28:15 by donglee           #+#    #+#             */
/*   Updated: 2020/04/08 17:28:25 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dst_len;
	size_t src_len;
	size_t i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (*dst)
		dst++;
	while (src[i] && i < dstsize - dst_len - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst_len + src_len);
}
