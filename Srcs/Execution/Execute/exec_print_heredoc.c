/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_print_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:23:02 by tripham           #+#    #+#             */
/*   Updated: 2025/04/27 20:03:27 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_ctrl_d(char *limiter)
{
	signals_initialize();
	ft_printf_fd(STDERR_FILENO, "bash: warning: here-document "
		"delimited by end-of-file (wanted `%s')\n", limiter);
}

int	print_heredoc(t_shell *mns, int fd, char *limiter, int is_exp)
{
	char	*line;

	set_hd_signal();
	while (1)
	{
		line = readline("> ");
		if (hd_abort(0) == 1)
		{
			mns->exitcode = 130;
			signals_initialize();
			return (-2);
		}
		if (!line)
			return (get_ctrl_d(limiter), free(line), 1);
		if (limiter && !ft_strcmp(line, limiter))
		{
			signals_initialize();
			return (free(line), 1);
		}
		if (is_exp == 0)
			hd_expansion_gen(mns, &line);
		ft_printf_fd (fd, "%s\n", line);
		free(line);
	}
	return (0);
}
