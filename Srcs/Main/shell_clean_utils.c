/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_clean_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:08:13 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/21 21:07:26 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_out(t_cmd *group, int id)
{
	int	i;

	i = 0;
	while (i < group[id].out_cnt)
	{
		free(group[id].out[i].val);
		i++;
	}
	free(group[id].out);
}

void	free_in(t_cmd *group, int id)
{
	int	i;

	i = 0;
	while (i < group[id].in_cnt)
	{
		free(group[id].in[i].val);
		i++;
	}
	free(group[id].in);
}
