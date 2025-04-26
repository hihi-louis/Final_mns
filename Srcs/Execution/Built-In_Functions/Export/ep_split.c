/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ep_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 03:53:09 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/20 08:39:50 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ep_end(char *input, int i, int size)
{
	while (i < size)
	{
		if ((i + 1 < size && input[i] == '+' && input[i + 1] == '=')
			|| (i < size && input[i] == '='))
			break ;
		else
			i++;
	}
	return (i);
}

char	**ep_split(t_shell *mns, char *input)
{
	int		start;
	int		end;
	int		i;
	char	**res;

	i = 0;
	start = 0;
	res = malloc(3 * sizeof(char *));
	if (!res)
		ft_bad_alloc(mns);
	end = ep_end(input, start, ft_strlen(input));
	res[0] = ft_substr(input, start, end - start);
	if (!res[0])
		ft_bad_alloc(mns);
	start = end;
	end = ft_strlen(input);
	res[1] = ft_substr(input, start, end - start);
	if (!res[1])
	{
		ft_free_process_2d(res, i);
		ft_bad_alloc(mns);
	}
	res[2] = NULL;
	return (res);
}
