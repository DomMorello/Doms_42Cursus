#include "minishell.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == ' ')
		return (TRUE);
	return (FALSE);
}

int pwd(char *line)
{
	char *cwd;
	char buf[100];
	int i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'p' && line[i + 1] == 'w' && line[i + 2] == 'd')
	{
		cwd = getcwd(buf, sizeof(buf));
		printf("%s\n", cwd);
		return 1;
	}
	return 0;
}

// cd 명령어 구현. 
int cd(char *line)
{
	char buf[100];
	int i;
	int ret;
	struct stat file;
	char *cwd;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'c' && line[i + 1] == 'd' && ft_isspace(line[i + 2]))
	{
		i += 3;
		while (ft_isspace(line[i]))
			i++;
		if ((ret = stat(&line[i], &file)) == -1)
			return -1;
		if (S_ISDIR(file.st_mode))
			if ((ret = chdir(&line[i])) == -1)
				return -1;
		cwd = getcwd(buf, sizeof(buf));
		printf("cwd: %s\n", cwd);
	}
	// else
	// {
	// 	printf("command not found : %s\n", &line[i]);
	// }
	/* 어떻게 하면 space를 기준으로 명령어 토큰을 나눌 수 있을까를 생각해라 */
	return 1;
}

int main(int argc, char *argv[], char *env[])
{
	char buf[100];
	int ret;
	char *line;
	char **commands;
	int i = 0;
	int j = 0;

	ret = 0;
	while (1)
	{
		ft_putstr_fd("\033[31mbash\033[0m\033[32m-\033[0m\033[33m3.2\033[0m$ ", 1);
		if ((ret = get_next_line(0, &line)) < 0)
		{
			printf("gnl error\n");
			free(line);
			exit(0);
		}
		cd(line); //cd 기초
		pwd(line);	//pwd 기초
	}
	return 0;
}
