/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:07:44 by tripham           #+#    #+#             */
/*   Updated: 2025/04/28 02:07:49 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_non_builtin_child(t_shell *mns, t_cmd *cmd, const int	*tmp)
{
	char	*command_path;

	handle_signals_default();
	close(tmp[0]);
	close(tmp[1]);
	command_path = found_command_path(mns, cmd->cmd_arg[0]);
	if (!command_path)
	{
		close(tmp[0]);
		close(tmp[1]);
		shell_clean(mns);
		exit(127);
	}
	execve(command_path, cmd->cmd_arg, mns->env);
	handle_execution_error(mns, command_path, cmd->cmd_arg);
}

void	exec_non_builtin(t_shell *mns, t_cmd *cmd, const int *tmp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("bash: fork failed");
		shell_clean(mns);
		return ;
	}
	if (pid == 0)
		exec_non_builtin_child(mns, cmd, tmp);
	wait_update(mns, pid);
	clean_heredoc_files(mns, cmd);
}

void	exec_builtin_child(t_shell *mns, t_cmd *cmd, const int	*tmp)
{
	int	code;

	close(tmp[0]);
	close(tmp[1]);
	exec_builtin(mns, cmd, tmp);
	code = mns->exitcode;
	shell_clean(mns);
	exit(code);
}
