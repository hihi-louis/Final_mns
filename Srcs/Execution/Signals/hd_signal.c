/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:39:41 by tripham           #+#    #+#             */
/*   Updated: 2025/04/27 20:49:34 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hd_abort(int hd_check)
{
	static int	hd_stop = 0;

	if (hd_check == 1)
	{
		hd_stop = 1;
	}
	if (hd_check == 2)
	{
		hd_stop = 0;
	}
	return (hd_stop);
}

int	event_hook(void)
{
	return (0);
}

void	handle_sigint_heredoc(int signal_val)
{
	(void)signal_val;
	ft_printf_fd(STDOUT_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_done = 1;
	hd_abort(1);
	signals_exit_configure(NULL);
}

void	set_hd_signal(void)
{
	struct sigaction	sa_hd;

	sigemptyset(&sa_hd.sa_mask);
	sa_hd.sa_handler = handle_sigint_heredoc;
	sa_hd.sa_flags = 0;
	sigaction(SIGINT, &sa_hd, NULL);
	rl_event_hook = event_hook;
}
