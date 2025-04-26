/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 00:26:51 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/21 13:46:48 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_getkey(t_shell *mns, char *line, int *i)
{
	int		start;
	char	*key;

	start = ++*i;
	while (line[*i])
	{
		if ((!ft_isalnum(line[*i]) && line[*i]) || line[*i] == '?')
			break ;
		(*i)++;
	}
	if (line[*i] == '?')
		(*i)++;
	key = ft_substr(line, start, *i - start);
	if (!key)
		ft_bad_alloc(mns);
	return (key);
}

void	hd_expand(t_shell *mns, char **temp, char **key)
{
	char	*str;

	if (ft_strcmp(*key, "?") && !get_env_val(mns, *key))
		return (free(*key));
	if (!ft_strcmp(*key, "?"))
		str = ft_itoa(mns->exitcode);
	else
		str = ft_strdup(get_env_val(mns, *key));
	if (!str)
		ft_bad_alloc(mns);
	if (str && ft_strlen(str) > 0)
	{
		if (!ft_append(temp, &str))
		{
			free(*key);
			ft_bad_alloc(mns);
		}
	}
	free(*key);
}

void	hd_expand_digit(t_shell *mns, char **key, char **temp)
{
	char	*str;

	str = ft_strdup(*key + 1);
	if (!ft_append(temp, &str))
	{
		free(*key);
		ft_bad_alloc(mns);
	}
	free(*key);
}
