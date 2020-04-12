/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 17:23:07 by donglee           #+#    #+#             */
/*   Updated: 2020/04/08 17:23:35 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	if ((result = (char *)malloc(sizeof(char) * len + 1)) == 0)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = 0;
	return (result);
}
