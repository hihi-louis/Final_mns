/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expansion_gen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:27:01 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/21 04:40:02 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exp_condition(char *str, int i, int sz)
{
	if (i + 1 < sz && str[i] == '$'
		&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		return (1);
	return (0);
}

static void	hd_subjoin(t_shell *mns, char **temp, char **line, t_point p)
{
	char	*post;

	post = ft_substr(*line, p.start, p.end - p.start);
	if (!post)
	{
		free(post);
		ft_bad_alloc(mns);
	}
	if (!ft_append(temp, &post))
		ft_bad_alloc(mns);
}

static void	hd_expansion_check(t_shell *mns, char **line, char **temp, int sz)
{
	t_point		p;
	int			i;
	char		*key;

	ft_bzero(&p, sizeof(t_point));
	i = 0;
	while (i < sz)
	{
		if (exp_condition(*line, i, sz))
		{
			p.end = i;
			hd_subjoin(mns, temp, line, p);
			key = hd_getkey(mns, *line, &i);
			p.start = i;
			if (!ft_isdigit(key[0]))
				hd_expand(mns, temp, &key);
			else
				hd_expand_digit(mns, &key, temp);
		}
		else
			i++;
	}
	p.end = i;
	if (p.start != p.end)
		hd_subjoin(mns, temp, line, p);
}

void	hd_expansion_gen(t_shell *mns, char **line)
{
	char	*temp;

	temp = ft_strdup("");
	if (!temp)
		ft_bad_alloc(mns);
	hd_expansion_check(mns, line, &temp, ft_strlen(*line));
	free(*line);
	*line = temp;
}
