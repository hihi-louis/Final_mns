/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:13:21 by tripham           #+#    #+#             */
/*   Updated: 2025/04/28 03:27:23 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_rd_helper(t_shell *mns, const int tmp[2])
{
	update_status(mns, 1);
	dup2(tmp[0], STDIN_FILENO);
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[0]);
	close(tmp[1]);
}

static void	dup_and_close(const int *tmp)
{
	dup2(tmp[0], STDIN_FILENO);
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[0]);
	close(tmp[1]);
}

void	exec_cmd(t_shell *mns, t_cmd *cmd)
{
	const int	tmp[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	if (handle_redirection(mns, cmd) == EXIT_FAILURE)
	{
		handle_rd_helper(mns, tmp);
		dup_and_close(tmp);
		return ;
	}
	if (!cmd->cmd_arg || !cmd->cmd_arg[0])
		update_status(mns, 0);
	else if (exec_cmd_check(cmd->cmd_arg[0]) && mns->is_pipe)
		exec_builtin_child(mns, cmd, tmp);
	else if (exec_cmd_check(cmd->cmd_arg[0]) && !mns->is_pipe)
		exec_builtin(mns, cmd, tmp);
	else if (mns->is_pipe)
		exec_non_builtin_child(mns, cmd, tmp);
	else
		exec_non_builtin(mns, cmd, tmp);
	dup_and_close(tmp);
}
