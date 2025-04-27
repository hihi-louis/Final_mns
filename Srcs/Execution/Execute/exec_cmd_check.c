/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:44:07 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/27 14:29:52 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_shell *mns, t_cmd *cmd, const int *tmp)
{
	char	*name;

	name = cmd->cmd_arg[0];
	if (!ft_strcmp(name, "echo"))
		bi_echo(mns, cmd);
	else if (!ft_strcmp(name, "cd"))
		bi_cd(mns, cmd);
	else if (!ft_strcmp(name, "pwd"))
		bi_pwd(mns, cmd);
	else if (!ft_strcmp(name, "env"))
		bi_env(mns, cmd);
	else if (!ft_strcmp(name, "export"))
		bi_export(mns, cmd);
	else if (!ft_strcmp(name, "unset"))
		bi_unset(mns, cmd);
	else if (!ft_strcmp(name, "exit"))
		bi_exit(mns, cmd, tmp);
}

int	exec_cmd_check(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}
