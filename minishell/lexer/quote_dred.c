#include "../minishell.h"

int make_dred_out(t_token *deleted, t_token *prev, int d_red_out)
{
	if (deleted && d_red_out && !ft_strncmp(deleted->data, ">", ft_strlen(">")))
	{
		prev->next = deleted->next;
		free(prev->data);
		prev->data = ft_strdup(">>");
		free(deleted->data);
		free(deleted);
		return (TRUE);
	}
	return (FALSE);
}

void check_dred_out(t_token *token)
{
	t_token	*tmp;
	t_token *tmp2;
	t_token *prev;
	int		d_red_out;
	
	tmp = token;
	tmp2 = token;
	while (tmp2)
	{
		tmp = tmp2;
		while (tmp)
		{
			d_red_out = FALSE;
			if (!ft_strncmp(tmp->data, ">", ft_strlen(">")))
				d_red_out = TRUE;
			prev = tmp;
			tmp = tmp->next;
			if (make_dred_out(tmp, prev, d_red_out))
				break ;
		}
		tmp2 = tmp2->next;
	}
}

void copy_without_quote(char *data, char *new, char quote_type)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] != quote_type)
			new[j++] = data[i];
		i++;
	}
	new[j] = 0;
}

void erase_quote(t_token *token, char quote_type)
{
	t_token	*tmp;
	char	*new;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == quote_type)
		{
			if ((new = (char *)malloc(sizeof(char) *
				ft_strlen(tmp->data) - 1)) == NULL)
				exit(-1);
			copy_without_quote(tmp->data, new, quote_type);
			free(tmp->data);
			tmp->data = new;
		}
		tmp = tmp->next;
	}
}