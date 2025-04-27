/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:39:39 by tripham           #+#    #+#             */
/*   Updated: 2025/04/27 19:07:38 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_rd_in(t_shell *mns, int *fd, int i, t_token *in)
{
	if (in[i].type == RD_AMBI)
		return (check_ambiguous_rd(mns, in[i].val, fd));
	if (*fd != -1)
		close (*fd);
	*fd = open(in[i].val, O_RDONLY);
	if (*fd < 0)
	{
		ft_printf_fd(2,
			"bash: %s: %s\n", in[i].val, strerror(errno));
		clean_heredoc_files(mns, mns->cmd_group);
		update_status(mns, 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	handle_rd_hd(int *fd, int *j, char **hd)
{
	if (*fd != -1)
		close (*fd);
	*fd = open(hd[*j], O_RDONLY);
	if (*fd < 0)
		return (EXIT_FAILURE);
	(*j)++;
	return (EXIT_SUCCESS);
}

static int	handle_infile(t_shell *mns, t_cmd *cmd, int i, int j)
{
	int	fd;

	fd = -1;
	while (++i < cmd->in_cnt)
	{
		if (cmd->in[i].type == RD_IN || cmd->in[i].type == RD_AMBI)
		{
			if (handle_rd_in(mns, &fd, i, cmd->in))
				return (EXIT_FAILURE);
		}
		else
		{
			if (handle_rd_hd(&fd, &j, cmd->heredoc))
				return (EXIT_FAILURE);
		}
	}
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

static int	handle_outfile(t_cmd *cmd)
{
	int	fd;
	int	i;

	i = 0;
	while (i < cmd->out_cnt)
	{
		if (cmd->out[i].type == RD_OUT)
			fd = open(cmd->out[i].val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (cmd->out[i].type == RD_APPEND)
			fd = open(cmd->out[i].val, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
		{
			i++;
			continue ;
		}
		if (fd < 0)
		{
			ft_printf_fd(STDERR_FILENO, "bash: %s: %s\n", cmd->out[i].val, strerror(errno));
			return (EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	handle_redirection(t_shell *mns, t_cmd *cmd)
{
	if (handle_infile(mns, cmd, -1, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (handle_outfile(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
