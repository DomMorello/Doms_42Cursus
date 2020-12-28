/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:33:12 by donglee           #+#    #+#             */
/*   Updated: 2020/12/28 14:11:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_env(void)
{
	while (g_env_list)
	{
		free(g_env_list->content);
		g_env_list = g_env_list->next;
	}
	ft_lstclear(&g_env_list, free);
}

void	free_cmds(char ***cmds)
{
	int i;
	int j;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	start_bash(char ***cmds)
{
	int i;

	i = 0;
	while (cmds[i])
	{
		handle_process(cmds[i]);
		i++;
	}
}

void	parse_to_start(t_token *token)
{
	char ***cmds;

	if (check_basic_grammar(token))
	{
		adjust_env(token);
		check_dred_out(token);
		erase_quote(token, CHAR_DQUOTE);
		erase_quote(token, CHAR_QUOTE);
		adjust_env_in_dquote(token);
		convert_exit_status(token);
		cmds = divide_semicolon(token);
		start_bash(cmds);
		free_cmds(cmds);
	}
}

int		main(int argc, char const *argv[], char **envp)
{
	t_token		*token;
	char		buf[BUF_SIZE];

	(void)argc;
	(void)argv;
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
	copy_environ(envp);
	while (TRUE)
	{
		g_pid = 0;
		handle_prompt(buf);
		token = tokenize_lexer(buf, ft_strlen(buf));
		if (!remove_empty_token(token))
		{
			free_all_tokens(token, free);
			continue ;
		}
		parse_to_start(token);
		free_all_tokens(token, free);
	}
	free_env();
	return (EXIT_SUCCESS);
}
