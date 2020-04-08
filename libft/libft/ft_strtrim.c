/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 17:31:46 by donglee           #+#    #+#             */
/*   Updated: 2020/04/08 21:00:39 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_first_len(char const *s1, char const *set)
{
	int len;
	int result;

	len = 0;
	result = 0;
	while (s1[len])
		len++;
	while (s1[len - 1] && is_set(set, s1[len - 1]))
		len--;
	while (s1[len - 1] && !is_set(set, s1[len - 1]))
	{
		result++;
		len--;
	}
	return (len + result);
}

static int	get_second_len(char const *s1, char const *set)
{
	int first_len;
	int second_len;
	int i;

	first_len = get_first_len(s1, set);
	i = 0;
	second_len = 0;
	while (s1[i] && is_set(set, s1[i]))
		i++;
	second_len = first_len - i;
	return (second_len);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*result;

	i = 0;
	j = 0;
	len1 = get_first_len(s1, set);
	len2 = get_second_len(s1, set);
	if ((result = (char *)malloc(sizeof(char) * len2 + 1)) == 0)
		return (NULL);
	while (s1[i] && is_set(set, s1[i]))
		i++;
	while (s1[i] && i < len1)
	{
		result[j] = s1[i];
		j++;
		i++;
	}
	result[j] = 0;
	return (result);
}
