/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:13:21 by tripham           #+#    #+#             */
/*   Updated: 2025/04/26 19:30:28 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_rd_helper(t_shell *mns, t_cmd *cmd, const int tmp[2])
{
	update_status(mns, 1);
	clean_heredoc_files(mns, cmd);
	if (mns->std_fd[0] != -2)
	{
		dup2(mns->std_fd[0], STDIN_FILENO);
		close(mns->std_fd[0]);
	}
	if (mns->std_fd[1] != -2)
	{
		dup2(mns->std_fd[1], STDOUT_FILENO);
		close(mns->std_fd[1]);
	}
	dup2(tmp[0], STDIN_FILENO);
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[0]);
	close(tmp[1]);
}

static void	dup_and_close(t_shell *mns, const int *tmp, t_cmd *cmd)
{
	clean_heredoc_files(mns, cmd);
	dup2(tmp[0], STDIN_FILENO);
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[0]);
	close(tmp[1]);
	if (mns->std_fd[0] != -2)
	{
		dup2(mns->std_fd[0], STDIN_FILENO);
		close(mns->std_fd[0]);
	}
	if (mns->std_fd[1] != -2)
	{
		dup2(mns->std_fd[1], STDOUT_FILENO);
		close(mns->std_fd[1]);
	}
}

void	exec_cmd(t_shell *mns, t_cmd *cmd)
{
	const int	tmp[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};
	char		*target;

	if (handle_redirection(mns, cmd) == EXIT_FAILURE)
	{
		handle_rd_helper(mns, cmd, tmp);
		return ;
	}
	if (!cmd->cmd_arg || !cmd->cmd_arg[0])
		update_status(mns, 0);
	if (!ft_strcmp(cmd->cmd_arg[0], "~"))
	{
		target = get_env_val(mns, "HOME");
		ft_printf_fd(2, "bash: %s: Is a directory\n", target);
		update_status(mns, 126);
	}
	else if (exec_cmd_check(cmd->cmd_arg[0]) && mns->is_pipe)
		exec_builtin_child(mns, cmd, tmp);
	else if (exec_cmd_check(cmd->cmd_arg[0]) && !mns->is_pipe)
		exec_builtin(mns, cmd);
	else if (mns->is_pipe)
		exec_non_builtin_child(mns, cmd, tmp);
	else
		exec_non_builtin(mns, cmd, tmp);
	dup_and_close(mns, tmp, cmd);
}
