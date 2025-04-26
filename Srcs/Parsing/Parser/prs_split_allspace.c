/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_split_allspace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:08:52 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/19 03:56:01 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prs_wordcnt(char *input)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (input[i])
	{
		if (ft_isallspace(input[i]))
			i = prs_skip_space(input, i);
		else
		{
			cnt++;
			i = prs_skip_word(input, i);
		}
	}
	return (cnt);
}

static char	**prs_splitting(char *in, char **res, int i, int lim)
{
	int		start;

	start = 0;
	while (in[start] && i < lim)
	{
		if (ft_isallspace(in[start]))
			start = prs_skip_space(in, start);
		else
		{
			if (!prs_split_word(in, res, &start, &i))
				return (NULL);
		}
	}
	return (res);
}

char	**prs_split_allspace(char *input)
{
	int		wordcnt;
	char	**final;
	char	**res;

	wordcnt = prs_wordcnt(input);
	final = (char **)malloc((wordcnt + 1) * sizeof (char *));
	if (!final)
		return (NULL);
	res = final;
	if (!prs_splitting(input, res, 0, wordcnt))
	{
		free(final);
		return (NULL);
	}
	final[wordcnt] = NULL;
	return (final);
}
