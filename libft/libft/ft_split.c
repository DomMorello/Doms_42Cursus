/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:51:51 by donglee           #+#    #+#             */
/*   Updated: 2020/04/08 17:00:53 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_each_len(char const *s, char c)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			len++;
		i++;
	}
	return (len);
}

static int	get_chunk_len(char const *s, char c)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			len++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (len);
}

static int	freedata(char **result, int i)
{
	while (i--)
		free(result[i]);
	free(result);
	return (0);
}

static int	alloc_arr(char const *s, char c, char ***result)
{
	int chunk;
	int each;
	int i;

	chunk = get_chunk_len(s, c);
	if ((*result = (char **)malloc(sizeof(char *) * chunk + 1)) == 0)
		return (0);
	(*result)[chunk] = 0;
	each = get_each_len(s, c);
	i = 0;
	while (i < chunk)
	{
		if (((*result)[i] = (char *)malloc(sizeof(char) * each + 1)) == 0)
			return (freedata((*result), i));
		i++;
	}
	return (1);
}

char		**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		k;

	k = 0;
	if (alloc_arr(s, c, &result) == 0)
		return (NULL);
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			j = 0;
			while (s[i] && s[i] != c)
				result[k][j++] = s[i++];
			result[k++][j] = 0;
		}
	}
	return (result);
}
