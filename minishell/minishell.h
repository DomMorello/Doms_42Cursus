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

// # define GREEN "\033[0;32m"
// # define LIGHT_BLUE "\033[0;34m"
// # define YELLOW "\033[0;33m"
// # define NC "\033[0m"

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PATH "PATH="
# define HOME "HOME="
# define USRBIN "/usr/bin"
# define OLDPWD "OLDPWD="
# define PWD2 "PWD="
# define N_OPTION "-n"

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

int get_next_line(int fd, char **line);

#endif
