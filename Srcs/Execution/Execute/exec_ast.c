/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:27:56 by tripham           #+#    #+#             */
/*   Updated: 2025/04/26 19:42:06 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	fork_and_exec_left(t_ast *node, t_shell *mns,
								int fd, int pipe_fd[2])
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == 0)
	{
		if (mns->std_fd[0] != -2)
			close(mns->std_fd[0]);
		if (mns->std_fd[1] != -2)
			close(mns->std_fd[1]);
		handle_signals_default();
		dup2(fd, STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		mns->is_pipe = true;
		exec_ast(node, mns);
		exit_code = mns->exitcode;
		shell_clean(mns);
		exit(exit_code);
	}
	return (pid);
}

static pid_t	fork_and_exec_right(t_ast *node, t_shell *mns,
								int fd, int pipe_fd[2])
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == 0)
	{
		if (mns->std_fd[0] != -2)
			close(mns->std_fd[0]);
		if (mns->std_fd[1] != -2)
			close(mns->std_fd[1]);
		handle_signals_default();
		dup2(fd, STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		mns->is_pipe = true;
		exec_ast(node, mns);
		exit_code = mns->exitcode;
		shell_clean(mns);
		exit(exit_code);
	}
	return (pid);
}

static void	exec_cmd_node(t_shell *mns, t_ast *node)
{
	if (mns->heredoc_failed)
	{
		mns->heredoc_failed = 0;
		return ;
	}
	exec_cmd(mns, &mns->cmd_group[node->cmd_index]);
	if (mns->std_fd[0] != -2)
		close(mns->std_fd[0]);
	if (mns->std_fd[1] != -2)
		close(mns->std_fd[1]);
}

static void	close_wait_clean_hd(t_shell *mns, int *pipe_fd,
				pid_t left_pid, pid_t right_pid)
{
	int	i;

	i = 0;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait_update(mns, left_pid);
	wait_update(mns, right_pid);
	while (i < mns->group_cnt)
	{
		clean_heredoc_files(mns, &mns->cmd_group[i]);
		i++;
	}
}

void	exec_ast(t_ast *node, t_shell *mns)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		exec_cmd_node(mns, node);
		return ;
	}
	if (pipe(pipe_fd) == -1)
		return (perror("pipe error"));
	left_pid = fork_and_exec_left(node->left, mns, pipe_fd[1], pipe_fd);
	right_pid = fork_and_exec_right(node->right, mns, pipe_fd[0], pipe_fd);
	if (left_pid == -1 || right_pid == -1)
		return (handle_fork_error(pipe_fd));
	close_wait_clean_hd(mns, pipe_fd, left_pid, right_pid);
	mns->is_pipe = false;
}
