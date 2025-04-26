/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hd_clean_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:40 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/22 22:44:00 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_group_index(t_shell *mns, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < mns->group_cnt)
	{
		if (&mns->cmd_group[i] == cmd)
			return (i);
		i++;
	}
	return (-1);
}

void	clean_heredoc_files(t_shell *mns, t_cmd *cmd)
{
	int		i;
	char	*file_name;
	int		group_index;

	group_index = get_cmd_group_index(mns, cmd);
	if (group_index == -1)
		return ;
	i = 0;
	while (i < cmd->heredoc_cnt)
	{
		file_name = heredoc_filename(group_index * 100 + i);
		unlink(file_name);
		free(file_name);
		free(cmd->heredoc[i]);
		cmd->heredoc[i] = NULL;
		i++;
	}
}
