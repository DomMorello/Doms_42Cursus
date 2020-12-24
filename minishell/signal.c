#include "./minishell.h"

void sig_int(int signo)
{
	(void)signo;
	if (g_pid == 0)
	{
		ft_putstr_fd("\b\b  \b\b", STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("\033[0;32mmongshell\033[0;34m$ \033[0m", STDERR);
		g_exit_status = 1;
	}
	else
		ft_putstr_fd("\n", STDERR);
}

void sig_quit(int signo)
{
	(void)signo;
	if (g_pid == 0)
		ft_putstr_fd("\b\b  \b\b", STDERR);
	else
		ft_putstr_fd("Quit: 3\n", STDERR);
}