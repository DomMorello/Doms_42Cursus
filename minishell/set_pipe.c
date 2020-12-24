#include "./minishell.h"

void set_pipe_child()
{
	close(g_pipe_fd[0]);
	dup2(g_pipe_fd[1], 1);
	close(g_pipe_fd[1]);
}

void set_pipe_parent()
{
	close(g_pipe_fd[1]);
	dup2(g_pipe_fd[0], 0);
	close(g_pipe_fd[0]);
}

int find_pipe(char *cmd[])
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "|", ft_strlen(cmd[i])
			> 1 ? ft_strlen(cmd[i]) : 1))
			return (TRUE);
		i++;
	}
	return (FALSE);
}