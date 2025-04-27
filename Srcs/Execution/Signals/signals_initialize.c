/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_initialize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:51:24 by tripham           #+#    #+#             */
/*   Updated: 2025/04/27 20:49:54 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h> 

int	signals_configure(int signal_val, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(signal_val, &sa, NULL) < 0)
	{
		perror("sigaction failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	signals_initialize(void)
{
	if (signals_configure(SIGINT, handle_sigint) == EXIT_FAILURE
		|| signals_configure(SIGQUIT, SIG_IGN) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	handle_sigint(int signal_val)
{
	(void)signal_val;
	ft_printf_fd(STDOUT_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signals_exit_configure(NULL);
}

void	signals_exit_configure(t_shell *mns)
{
	static t_shell	*current_mns;

	if (mns)
		current_mns = mns;
	else if (current_mns)
		current_mns->exitcode = SIGINT + 128;
}
