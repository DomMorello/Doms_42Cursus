#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int ft_strlen(char *s);
char *ft_strchr(char *s, int c);
char *ft_strdup(char *s);
char *ft_substr(char *s, unsigned start, int len);
char *ft_strjoin(char *s1, char *s2);
int get_next_line(int fd, char **line);

#endif
