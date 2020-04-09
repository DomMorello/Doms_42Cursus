/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 15:39:05 by donglee           #+#    #+#             */
/*   Updated: 2020/04/09 17:57:08 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		is_newline(char **save, char **line);
int		get_next_line(int fd, char **line);
char	*ft_strjoindel(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char const *src, size_t size);
size_t	ft_strlen(char const *s);
char	*ft_strchr(char const *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(char const *s1);
void	ft_strdel(char **as);

#endif
