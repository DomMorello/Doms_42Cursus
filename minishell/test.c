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

# define LS "/bin/ls"

size_t ft_strlen(const char *s)
{
	size_t len = 0;

	while (s[len])
		len++;
	return (len);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*result;
	size_t	n_len;
	size_t	i;
	size_t	check;
	size_t	flag;

	result = (char *)haystack;
	i = 0;
	if ((n_len = ft_strlen(needle)) == 0)
		return (&result[i]);
	while (haystack[i] && i < len)
	{
		check = i;
		flag = 0;
		while (haystack[check] == needle[flag] && i + flag < len)
		{
			if (flag++ == n_len - 1)
				return (&result[i]);
			check++;
		}
		i++;
	}
	return (NULL);
}

extern char **environ;

int main(int argc, char *argv[])
{
	// if (ft_strnstr(argv[1], LS, ft_strlen(LS)))
	// {
	// 	pid_t pid;

	// 	pid = fork();
	// 	int c_stat;

	// 	wait(&(c_stat));
	// 	if (pid == 0)
	// 	{
	// 		char *data1[] = {LS, 0};
	// 		char *data2[] = {0};
	// 		execve(argv[1], data1, data2);
	// 	}
	// }	
	char **new_argv;
	char command[] = "ls";
	int i;

	new_argv = (char **)malloc(sizeof(char *) * (argc + 1));

	new_argv[0] = command;

	for (i = 1; i < argc; i++)
	{
		new_argv[i] = argv[i];
	}

	new_argv[argc] = NULL;
	if ((execve("/bin/ls", new_argv, environ)) == -1)
	{
		printf("%s\n", strerror(errno));
		return -1;
	}
	printf("this must not be seen\n");
	
	return 0;
}
