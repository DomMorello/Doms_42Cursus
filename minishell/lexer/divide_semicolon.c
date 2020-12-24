#include "../minishell.h"

int get_num_cmdline(t_token *token)
{
	int		len;
	t_token	*tmp;

	len = 0;
	tmp = token;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, ";", 1) && tmp->next)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int get_num_cmd(t_token **token)
{
	int len;

	len = 0;
	while (*token)
	{
		if (!ft_strncmp((*token)->data, ";", 1))
		{
			*token = (*token)->next;
			break ;
		}
		len++;
		*token = (*token)->next;
	}
	return (len);
}

void copy_token_to_char(t_token **token, int num_cmd, char **cmds)
{
	int i;

	i = 0;
	while (i < num_cmd)
	{
		if (!ft_strncmp((*token)->data, ";", 1))
		{
			*token = (*token)->next;
			continue ;
		}
		cmds[i] = ft_strdup((*token)->data);
		*token = (*token)->next;
		i++;
	}
	cmds[i] = NULL;
}

char ***alloc_cmds(t_token *token, char ***cmds, int len)
{
	int		i;
	int		num_cmd;
	t_token	*tmp;
	t_token	*tmp2;

	i = 0;
	tmp = token;
	tmp2 = token;
	if ((cmds = (char ***)malloc(sizeof(char **) * len + 1)) == NULL)
		exit(-1);
	cmds[len] = NULL;
	while (i < len)
	{
		num_cmd = get_num_cmd(&tmp);
		if ((cmds[i] = (char **)malloc(sizeof(char *) * num_cmd + 1)) == NULL)
			exit(-1);
		copy_token_to_char(&tmp2, num_cmd, cmds[i]);
		cmds[i][num_cmd] = NULL;
		i++;
	}
	return (cmds);
}

char ***divide_semicolon(t_token *token)
{
	char	***cmds;
	int		len;
	int		i;

	i = 0;
	len = 0;
	len = get_num_cmdline(token) + 1;
	cmds = alloc_cmds(token, cmds, len);
	return (cmds);
}