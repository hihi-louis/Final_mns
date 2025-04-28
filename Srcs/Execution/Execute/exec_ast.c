/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:27:56 by tripham           #+#    #+#             */
/*   Updated: 2025/04/29 02:55:47 by tripham          ###   ########.fr       */
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
		handle_signals_default();
		dup2(fd, STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
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
}

static void	exec_pipe_node(t_ast *node, t_shell *mns)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe error"));
	left_pid = fork_and_exec_left(node->left, mns, pipe_fd[1], pipe_fd);
	right_pid = fork_and_exec_right(node->right, mns, pipe_fd[0], pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close_wait_clean_hd(mns, pipe_fd, left_pid, right_pid);
	mns->is_pipe = false;
}

void	exec_ast(t_ast *node, t_shell *mns)
{
	if (!node)
		return ;
	if (mns->heredoc_failed)
	{
		mns->exitcode = 130;
		mns->heredoc_failed = 0;
		return ;
	}
	if (node->type == NODE_PIPE)
	{
		exec_pipe_node(node, mns);
		return ;
	}
	else if (node->type == NODE_CMD)
	{
		exec_cmd_node(mns, node);
		return ;
	}
}
