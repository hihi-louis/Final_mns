/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_group_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 00:34:41 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/15 16:27:38 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lx_skip_cmd(char *input, int index)
{
	while (input[index])
	{
		if (ft_is_dquote(input[index]))
			lx_skip_dquote(input, &index);
		else if (input[index] == '|')
			return (index);
		else
			index++;
	}
	return (index);
}

int	lx_split_group(char *in, char **res, int *start, int *i)
{
	int	end;

	end = lx_skip_cmd(in, *start);
	res[*i] = ft_substr(in, *start, end - *start);
	if (!res[*i])
	{
		ft_free_process_2d(res, *i);
		return (0);
	}
	*start = end + 1;
	(*i)++;
	return (1);
}
