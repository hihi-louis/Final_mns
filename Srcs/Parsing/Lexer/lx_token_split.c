/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:38:56 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/13 13:39:12 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lx_wordcnt(char	*input)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (input[i])
	{
		if (ft_isallspace(input[i]))
			i = lx_skip_space(input, i);
		else if (ft_rd_op(input, i))
		{
			cnt++;
			i += ft_rd_op(input, i);
		}
		else
		{
			cnt++;
			i = lx_skip_word(input, i);
		}
	}
	return (cnt);
}

static char	**lx_splitting(char *in, char **res, int i, int lim)
{
	int		start;

	start = 0;
	while (in[start] && i < lim)
	{
		if (ft_isallspace(in[start]))
			start = lx_skip_space(in, start);
		else if (ft_rd_op(in, start))
		{
			if (!lx_split_rd_op(in, res, &start, &i))
				return (NULL);
		}
		else
		{
			if (!lx_split_word(in, res, &start, &i))
				return (NULL);
		}
	}
	return (res);
}

char	**lx_token_split(t_shell *mns, char *input, int i)
{
	int		wordcnt;
	char	**final;
	char	**res;

	wordcnt = lx_wordcnt(input);
	final = (char **)malloc((wordcnt + 1) * sizeof (char *));
	if (!final)
		return (NULL);
	res = final;
	if (!lx_splitting(input, res, 0, wordcnt))
	{
		free(final);
		return (NULL);
	}
	final[wordcnt] = NULL;
	mns->cmd_group[i].token_cnt = wordcnt;
	return (final);
}
