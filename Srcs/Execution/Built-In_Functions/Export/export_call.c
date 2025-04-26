/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:00:53 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/25 11:39:23 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ep_add(t_shell *mns, char *name, char *str, int pos)
{
	char	*temp1;
	char	*temp2;

	if (pos > -1)
	{
		if (!str || !str[0])
			return ;
		temp2 = ft_strdup(str + 2);
		if (!ft_append(&mns->env[pos], &temp2))
			ft_bad_alloc(mns);
	}
	else
	{
		if (!str || !str[0])
			return ;
		temp1 = ft_strdup(name);
		temp2 = ft_strdup(str + 1);
		if (!ft_append(&temp1, &temp2))
			ft_bad_alloc(mns);
		env_append(mns, temp1);
		free(temp1);
	}
}

static void	ep_variable(t_shell *mns, t_cmd *cmd, int i)
{
	int		pos;
	char	**temp;

	while (i < cmd->arg_cnt)
	{
		temp = ep_split(mns, cmd->cmd_arg[i]);
		if (!temp)
			ft_bad_alloc(mns);
		if (!ep_pre_validation(mns, temp))
			return ;
		pos = ep_check_exist(mns, temp[0], &temp);
		if (temp [1] && temp[1][0] && temp[1][0] == '+')
			ep_add(mns, temp[0], temp[1], pos);
		else if (pos > -1)
			ep_replace(mns, cmd->cmd_arg[i], pos);
		else
			env_append(mns, cmd->cmd_arg[i]);
		i++;
		ft_free_2d((void **)temp);
	}
}

void	bi_export(t_shell *mns, t_cmd *cmd)
{
	if (cmd->arg_cnt == 1)
		ep_standalone(mns, -1, ft_2d_len(mns->env));
	else if (cmd->arg_cnt > 1)
		ep_variable(mns, cmd, 1);
}
