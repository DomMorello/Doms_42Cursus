#include "minishell.h"

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

t_list *g_env_list;
t_list g_env_head;

extern char **environ;

// void copy_environ(void)
// {
// 	int i;
// 	t_list *tmp;

// 	g_env_head.content = ft_strdup(environ[0]);
// 	g_env_head.next = NULL;
// 	g_env_list = &g_env_head;
// 	i = 1;
// 	while (environ[i])
// 	{
// 		tmp = ft_lstnew(ft_strdup(environ[i]));
// 		ft_lstadd_back(&g_env_list, tmp);
// 		i++;
// 	}
// }

int main()
{


    return 0;
}
