/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 15:34:00 by donglee           #+#    #+#             */
/*   Updated: 2020/04/09 17:53:51 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t i;

	src_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}

char	*ft_strjoindel(char *s1, char *s2)
{
	char	*ret;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len;

	len_s1 = 0;
	len_s2 = ft_strlen(s2);
	if (s1)
		len_s1 = ft_strlen(s1);
	len = len_s1 + len_s2;
	if ((ret = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(ret, s1, (len_s1 + 1));
		ft_strdel(&s1);
	}
	ft_strlcpy(ret + len_s1, s2, (len_s2 + 1));
	return (ret);
}

int		is_newline(char **save, char **line)
{
	char	*found;
	size_t	end;
	size_t	len;

	len = 0;
	found = NULL;
	if ((found = ft_strchr(*save, '\n')))
	{
		end = found - *save;
		len = ft_strlen(found);
		*line = ft_substr(*save, 0, end);
		ft_strlcpy(*save, (found + 1), (len + 1));
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			bytes_read;
	static char	*save[1024];
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (save[fd] && is_newline(&save[fd], line) == 1)
		return (1);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = 0;
		if (!(save[fd] = ft_strjoindel(save[fd], buffer)))
			return (-1);
		if (is_newline(&save[fd], line) == 1)
			return (1);
	}
	if (save[fd] && *save[fd])
		*line = ft_strdup(save[fd]);
	else if (bytes_read == -1 || bytes_read == 0)
		*line = ft_strdup("");
	ft_strdel(&save[fd]);
	return (bytes_read);
}
