/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:43:20 by tripham           #+#    #+#             */
/*   Updated: 2025/04/18 20:36:16 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_special_cmd_error(t_shell *mns, char *cmd)
{
	if (!cmd || !cmd[0])
	{
		ft_printf_fd(STDERR_FILENO, "command '%s' not found\n", cmd);
		update_status(mns, 127);
		return (1);
	}
	if (!ft_strcmp(cmd, "."))
	{
		ft_printf_fd(STDERR_FILENO,
			"bash: .: filename argument required\n"
			".: usage: . filename [arguments]\n");
		update_status(mns, 2);
		return (1);
	}
	if (!ft_strcmp(cmd, ".."))
	{
		ft_printf_fd(STDERR_FILENO, "%s: command not found\n", cmd);
		update_status(mns, 127);
		return (1);
	}
	return (0);
}

int	check_error(t_shell *mns, char *cmd)
{
	if (is_special_cmd_error(mns, cmd))
		return (EXIT_FAILURE);
	if (access(cmd, F_OK) != 0)
	{
		ft_printf_fd(STDERR_FILENO, "%s: No such file or directory\n", cmd);
		update_status(mns, 127);
		return (EXIT_FAILURE);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_printf_fd(STDERR_FILENO, "%s: Permission denied\n", cmd);
		update_status(mns, 126);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
