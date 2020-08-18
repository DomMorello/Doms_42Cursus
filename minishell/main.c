#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == ' ')
		return (TRUE);
	return (FALSE);
}

// cd 명령어 구현. 
// int parse_line(char *line)
// {
// 	char buf[100];
// 	int i;
// 	int ret;
// 	struct stat file;
// 	char *cwd;

// 	i = 0;
// 	while (ft_isspace(line[i]))
// 		i++;
// 	if (line[i] == 'c' && line[i + 1] == 'd' && ft_isspace(line[i + 2]))
// 	{
// 		i += 3;
// 		while (ft_isspace(line[i]))
// 			i++;
// 		if ((ret = stat(&line[i], &file)) == -1)
// 			return -1;
// 		if (S_ISDIR(file.st_mode))
// 			if ((ret = chdir(&line[i])) == -1)
// 				return -1;
// 		cwd = getcwd(buf, sizeof(buf));
// 		printf("cwd: %s\n", cwd);
// 	}
// 	else
// 	{
// 		printf("command not found : %s\n", &line[i]);
// 	}
// 	/* 어떻게 하면 space를 기준으로 명령어 토큰을 나눌 수 있을까를 생각해라 */
// 	return 1;
// }

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

int main(int argc, char *argv[], char *env[])
{
	char buf[100];
	int ret;
	char *line;
	char **commands;
	int i = 0;

	ret = 0;
	while (1)
	{
		ft_putstr_fd("\033[31mbash\033[0m\033[32m-\033[0m\033[33m3.2\033[0m$ ", 1);
		if ((ret = get_next_line(0, &line)) < 0)
		{
			printf("gnl error\n");
			exit(0);	
		}
		// parse_line(line);
		commands = ft_split(line, ';');
		i = 0;
		while (commands[i])
		{
			printf("%s\n", commands[i]);
			i++;
		}
	}
	return 0;
}
