/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:43:50 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:43:51 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	frees the g_env_list strings and all nodes which are copy of environment.
*/

void	free_env(void)
{
	while (g_env_list)
	{
		free(g_env_list->content);
		g_env_list = g_env_list->next;
	}
	ft_lstclear(&g_env_list, free);
}

/*
**	frees three dimensional array(tokens).
*/

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

/*
**	starts processing commands divided by semicolons.
*/

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

/*
**	checks basic grammar exceptions and handles addition parising process.
*/

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

/*
**	handles signal, prompt, parsing, and start to launch bash.
*/

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
