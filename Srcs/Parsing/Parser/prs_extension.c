/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_extension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:59:48 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/26 03:06:29 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prs_check(t_shell *mns, int i, int alpha, int pipe)
{
	int	size;

	size = ft_strlen(mns->full_cmd_line);
	while (i < size)
	{
		if (alpha == 0 && mns->full_cmd_line[i] == '|')
			return (0);
		if (!ft_isallspace(mns->full_cmd_line[i])
			&& mns->full_cmd_line[i] != '|')
		{
			alpha = 1;
			pipe = 0;
		}
		else if (alpha == 1 && mns->full_cmd_line[i] == '|')
		{
			alpha = 0;
			pipe = 1;
		}
		i++;
	}
	if (pipe == 1 && alpha == 0)
		return (0);
	return (1);
}

static int	prs_arg_check(t_shell *mns)
{
	int		i;
	char	open;

	i = 0;
	open = 'e';
	while (mns && mns->full_cmd_line[i])
	{
		if ((mns->full_cmd_line[i] == '\''
				|| mns->full_cmd_line[i] == '\"') && open == 'e')
			open = mns->full_cmd_line[i];
		else if ((mns->full_cmd_line[i] == '\''
				|| mns->full_cmd_line[i] == '\"')
			&& open == mns->full_cmd_line[i])
			open = 'e';
		i++;
	}
	if (open != 'e')
	{
		ft_printf_fd(2,
			"bash: syntax error near unexpected token `%c'\n", open);
		mns->exitcode = 2;
		mns->shell_err = -2;
		return (0);
	}
	return (1);
}

int	prs_extra_check(t_shell *mns)
{
	if (!prs_arg_check(mns))
		return (0);
	else if (!prs_check(mns, 0, 0, 0))
	{
		ft_printf_fd(2, "bash: syntax error near unexpected token `|'\n");
		mns->exitcode = 2;
		mns->shell_err = -2;
		return (0);
	}
	return (1);
}
