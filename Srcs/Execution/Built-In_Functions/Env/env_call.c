/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:23:09 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/20 06:01:30 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_append(t_shell *mns, char *str)
{
	if (!mns->env || !ft_append_2d(&mns->env, str))
		ft_bad_alloc(mns);
}

void	bi_env(t_shell *mns, t_cmd *cmd)
{
	if (cmd->arg_cnt == 1)
		env_standalone(mns);
	else if (cmd->arg_cnt > 1)
	{
		ft_printf_fd(2, "env: '%s': No such file or directory\n",
			cmd->cmd_arg[1]);
		update_status(mns, 127);
	}
}
