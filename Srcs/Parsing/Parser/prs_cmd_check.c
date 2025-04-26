/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:39:14 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/20 04:08:31 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prs_cmd_check(t_shell *mns)
{
	int	i;
	int	j;

	i = 0;
	while (i < mns->group_cnt)
	{
		j = 0;
		while (j < mns->cmd_group[i].token_cnt)
		{
			if (mns->cmd_group[i].list[j].type == SIGN
				&& j == mns->cmd_group[i].token_cnt -1)
			{
				ft_printf_fd(2,
					"bash: syntax error: unexpected token `newline'\n");
				update_status(mns, 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
