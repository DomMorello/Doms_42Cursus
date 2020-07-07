#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		is_newline(char *save, char **line);
int		get_next_line(char **line);
char	*ft_strjoindel(char *s1, char *s2);
int	    ft_strlcpy(char *dst, char *src, int size);
int	    ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s1);
void	ft_strdel(char **as);

#endif