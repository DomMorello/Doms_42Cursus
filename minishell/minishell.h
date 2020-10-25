#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include "./libft/libft.h"
#include <malloc.h>

// # define GREEN "\033[0;32m"
// # define LIGHT_BLUE "\033[0;34m"
// # define YELLOW "\033[0;33m"
// # define NC "\033[0m"

# define TRUE 1
# define FALSE 0
# define ERROR -1

//다 삭제해야된다.
# define USR_BIN_STR "/usr/bin/"
# define BIN_STR "/bin/"
# define USR_BIN_NUM 1
# define BIN_NUM 2

# define PATH "PATH="

int get_next_line(int fd, char **line);

#endif
