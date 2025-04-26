/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:58:07 by tripham           #+#    #+#             */
/*   Updated: 2025/04/26 19:57:25 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*status_one(t_shell *mns, char *fi_na, char *lim_copy, int fd)
{
	free(lim_copy);
	close(fd);
	update_status(mns, 1);
	signals_initialize();
	return (fi_na);
}

char	*status_zero(t_shell *mns, char *fi_na, char *lim_copy, int fd)
{
	mns->exitcode = 1;
	free(fi_na);
	free(lim_copy);
	signals_initialize();
	close(fd);
	return (NULL);
}

char	*status_minus_two(t_shell *mns, char *fi_na, char *lim_copy, int fd)
{
	int	i;

	i = 0;
	hd_abort(2);
	while (i < mns->group_cnt)
	{
		clean_heredoc_files(mns, &mns->cmd_group[i]);
		i++;
	}
	free(fi_na);
	free(lim_copy);
	close(fd);
	signals_initialize();
	return (NULL);
}

int	prepare_lim_copy(char **lim_copy, char *limiter)
{
	*lim_copy = ft_strdup(limiter);
	if (!*lim_copy)
		return (1);
	return (0);
}

int	prepare_fi_na(char **fi_na, int index)
{
	*fi_na = heredoc_filename(index);
	if (!*fi_na)
		return (1);
	return (0);
}
