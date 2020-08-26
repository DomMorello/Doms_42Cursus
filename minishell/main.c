#include "minishell.h"

extern char **environ;

static int	ft_isspace(char c)
{
	if (c == '\t' || c == ' ')
		return (TRUE);
	return (FALSE);
}

// export basic 
int ft_export(char *line, t_list *list)
{
	int i = 0;

	if (!ft_strncmp(line, "export", ft_strlen("export")))
	{
		// if (!ft_isspace(line[i + ft_strlen("export")]))
		// 	return 0;
		while (list)
		{
			write(1, "declare -x ", 11);
			printf("%s\n", (char *)list->content);
			list = list->next;
		}
	}
}

// env basic
int ft_env(char *line, t_list *list)
{
	if (line[0] == 'e' && line[1] == 'n' && line[2] == 'v')
	{
		/* env 현재 파일 출력 */
		while (list)
		{
			printf("%s\n", (char *)list->content);
			list = list->next;
		}
	}
}

//pwd 구현 
int pwd(char *line)
{
	char *cwd;
	char buf[100];
	int i;

	i = 0;
	if (line[0] == 'p' && line[1] == 'w' && line[2] == 'd')
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

	if (line[0] == 'c' && line[1] == 'd' && ft_isspace(line[2]))
	{
		i = 3;
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

int main(int argc, char *argv[])
{
	/* env linked list 부분 일단 */
	t_list head;
	head.content = environ[0];
	head.next = NULL;
	t_list *list = &head;

	int i = 1;
	while (environ[i])
	{
		t_list *tmp = ft_lstnew(environ[i]);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	/* env ------------------- */

	char buf[100];
	int ret;
	char *line;
	char **commands;
	i = 0;
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
		while (ft_isspace(line[i]))
			i++;
		cd(&line[i]);
		pwd(&line[i]);
		ft_env(&line[i], list);
		ft_export(&line[i], list);
	}
	return 0;
}
