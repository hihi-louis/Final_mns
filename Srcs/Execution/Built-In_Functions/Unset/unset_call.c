/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_call.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:36:23 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/20 00:59:22 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	rm_env(int j, char ***env)
{
	int	i;

	i = j;
	free((*env)[i]);
	while ((*env)[i])
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	(*env)[i] = NULL;
}

void	unset_env_var(char *key, char ***env)
{
	int		j;
	size_t	keylen;
	char	*safe;

	j = 0;
	while ((*env)[j])
	{
		safe = ft_strchr((*env)[j], '=');
		if (!safe)
		{
			j++;
			continue ;
		}
		keylen = safe - (*env)[j];
		if (ft_strncmp((*env)[j], key, keylen) == 0
			&& (*env)[j][keylen] == '=')
		{
			rm_env(j, env);
			break ;
		}
		j++;
	}
}

int	bi_unset(t_shell *mns, t_cmd *cmd)
{
	int		i;
	int		error;

	i = 1;
	error = 0;
	while (cmd->cmd_arg[i])
	{
		if (cmd->cmd_arg[i][0] == '-')
		{
			ft_printf_fd(2, "bash: unset: %c%c: invalid option\n",
				cmd->cmd_arg[i][0], cmd->cmd_arg[i][1]);
			ft_printf_fd(2, "unset: usage: unset [-f] [-v] [-n] [name ...]\n");
			error = 2;
		}
		unset_env_var(cmd->cmd_arg[i], &mns->env);
		i++;
	}
	return (update_status(mns, error));
}
