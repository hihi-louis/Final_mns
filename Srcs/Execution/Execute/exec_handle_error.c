/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:46:16 by tripham           #+#    #+#             */
/*   Updated: 2025/04/26 17:24:52 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_execution_error(t_shell *mns, char *command_path,
		char **splitted_command)
{
	ft_printf_fd(2, "bash: %s: %s\n", *splitted_command, strerror(errno));
	if (command_path)
		free(command_path);
	shell_clean(mns);
	exit(126);
}

void	handle_command_error(char **command, char *message)
{
	ft_printf_fd(2, "bash: %s: %s\n", *command, message);
	ft_free_2d((void **)command);
	exit(127);
}

void	handle_open_error(char *file_name, int which_pipe_end)
{
	ft_printf_fd(2, "bash: %s: %s\n", file_name, strerror(errno));
	close(which_pipe_end);
}

void	handle_fork_error(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
	perror("bash: fork\n");
	exit (1);
}
