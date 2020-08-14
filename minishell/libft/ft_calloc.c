/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 17:58:37 by donglee           #+#    #+#             */
/*   Updated: 2020/04/07 17:58:57 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char *result;

	if ((result = (char *)malloc(count * size)) == 0)
		return (NULL);
	ft_bzero(result, count * size);
	return ((void *)result);
}
