/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:33:58 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/20 03:48:44 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printf_echo_arg(t_shell *mns, char *arg)
{
	char	*expanded;

	expanded = expand_titled(mns, arg);
	ft_printf_fd(1, "%s", expanded);
	if (expanded != arg)
		free(expanded);
}

static bool	is_n_flag(char *arg)
{
	int	j;

	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	j = 2;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (false);
		j++;
	}
	return (true);
}

int	bi_echo(t_shell *mns, t_cmd *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (cmd->cmd_arg[i] && is_n_flag(cmd->cmd_arg[i]))
	{
		newline = false;
		i++;
	}
	while (cmd->cmd_arg[i])
	{
		printf_echo_arg(mns, cmd->cmd_arg[i]);
		if (cmd->cmd_arg[i + 1])
			ft_printf_fd(1, " ");
		i++;
	}
	if (newline)
		ft_printf_fd(1, "\n");
	update_status(mns, 0);
	return (EXIT_SUCCESS);
}
