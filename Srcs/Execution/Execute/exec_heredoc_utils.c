/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:45:27 by tripham           #+#    #+#             */
/*   Updated: 2025/04/26 19:55:04 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_check_quotes(t_shell *mns, char **limiter)
{
	char	c;
	char	*temp;

	if (!limiter || !*limiter)
		return (0);
	c = **limiter;
	temp = lx_qmarks_eli(mns, *limiter, 0, 0);
	free(*limiter);
	*limiter = temp;
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*heredoc_filename(int index)
{
	char	*filename;
	char	*index_str;

	index_str = ft_itoa(index);
	if (index_str == NULL)
	{
		perror("heredoc_filename failed");
		return (NULL);
	}
	filename = ft_strjoin(".heredoc_tmp_", index_str);
	if (filename == NULL)
	{
		free(index_str);
		perror("heredoc_filename failed");
		return (NULL);
	}
	free(index_str);
	return (filename);
}

char	*heredoc_tmp(t_shell *mns, char *limiter, int index)
{
	char	*fi_na;
	char	*lim_copy;
	int		fd;
	int		is_exp;
	int		status;

	if (prepare_lim_copy(&lim_copy, limiter))
		return (NULL);
	if (prepare_fi_na(&fi_na, index))
		return (free(lim_copy), NULL);
	fd = open(fi_na, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open failed"), free(fi_na), NULL);
	is_exp = exp_check_quotes(mns, &lim_copy);
	if (!lim_copy)
		return (free(fi_na), close(fd), NULL);
	status = print_heredoc(mns, fd, lim_copy, is_exp);
	if (status == 1)
		return (status_one(mns, fi_na, lim_copy, fd));
	else if (status == 0)
		return (status_zero(mns, fi_na, lim_copy, fd));
	else if (status == -2)
		return (status_minus_two(mns, fi_na, lim_copy, fd));
	return (free(lim_copy), fi_na);
}

void	heredoc_expand_all(t_shell *mns)
{
	int		i;
	int		j;
	char	*tmpfile;
	t_cmd	*cmd;

	i = 0;
	while (i < mns->group_cnt)
	{
		cmd = &mns->cmd_group[i];
		j = 0;
		while (j < cmd->heredoc_cnt)
		{
			tmpfile = heredoc_tmp(mns, cmd->heredoc[j], i * 100 + j);
			if (!tmpfile)
			{
				mns->heredoc_failed = 1;
				return ;
			}
			free(cmd->heredoc[j]);
			cmd->heredoc[j] = tmpfile;
			j++;
		}
		i++;
	}
}
