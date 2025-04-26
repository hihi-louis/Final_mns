/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:17:55 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/18 18:38:41 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prs_skip_space(char *input, int index)
{
	while (ft_isallspace(input[index]) && input[index])
		index++;
	return (index);
}

int	prs_skip_dquote(char *input, int *index)
{
	char	c;

	c = input[*index];
	(*index)++;
	while (input[*index])
	{
		if (input[*index] != c)
			(*index)++;
		else
			break ;
	}
	return (++(*index));
}

int	prs_skip_word(char *input, int index)
{
	while (input[index] && !ft_isallspace(input[index]))
	{
		if (ft_is_dquote(input[index]))
			prs_skip_dquote(input, &index);
		else
			index++;
	}
	return (index);
}

int	prs_split_word(char *in, char **res, int *start, int *i)
{
	int	end;

	end = prs_skip_word(in, *start);
	res[*i] = ft_substr(in, *start, end - *start);
	if (!res[*i])
	{
		ft_free_process_2d(res, *i);
		return (0);
	}
	*start = end;
	(*i)++;
	return (1);
}
