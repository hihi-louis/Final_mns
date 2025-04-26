/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_group_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:27:08 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/26 00:47:06 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lx_groupcnt(char *input)
{
	int	i;
	int	cnt;
	int	size;

	i = 0;
	cnt = 0;
	size = ft_strlen(input);
	while (i < size)
	{
		if (ft_is_dquote(input[i]))
			lx_skip_dquote(input, &i);
		else if (i + 1 < size && input[i] == '|' && input[i] != input[i + 1])
		{
			cnt++;
			i++;
		}
		else
			i++;
	}
	return (cnt + 1);
}

static char	**lx_splitting(char *in, char **res, int lim)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i < lim && in[start])
		lx_split_group(in, res, &start, &i);
	return (res);
}

char	**lx_group_split(t_shell *mns, char *input)
{
	int		groupcnt;
	char	**final;
	char	**res;

	groupcnt = lx_groupcnt(input);
	final = (char **)malloc((groupcnt + 1) * sizeof (char *));
	res = final;
	if (!lx_splitting(input, res, groupcnt))
	{
		free(final);
		return (NULL);
	}
	final[groupcnt] = NULL;
	mns->group_cnt = groupcnt;
	return (final);
}
