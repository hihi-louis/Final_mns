/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:31:36 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/21 13:32:49 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exp_new_strdup(const char *s)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(s) + 1);
	if (res == NULL)
		return (NULL);
	while (s[j])
	{
		if (ft_isallspace(s[j]))
		{
			res[i] = s[j];
			j = lx_skip_space((char *)s, j);
		}
		else
		{
			res[i] = s[j];
			j++;
		}
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	exp_validation(char *key)
{
	if (ft_isdigit(key[0]))
		return (1);
	return (2);
}

static char	*exp_string(t_shell *mns, char *str, int *i)
{
	int		start;
	char	op;
	char	*key;

	op = str[*i];
	start = *i;
	++*i;
	while (str[*i])
	{
		if (str[*i] == op)
		{
			op = 'e';
			(*i)++;
			break ;
		}
		(*i)++;
	}
	if (op == 'e')
		key = ft_substr(str, start, *i - start);
	else
		key = ft_substr(str, start, *i - start);
	if (!key)
		ft_bad_alloc(mns);
	return (key);
}

char	*exp_getkey(t_shell *mns, char *str, int *i, char open)
{
	int		start;
	char	*key;

	start = ++*i;
	if (ft_is_dquote(str[*i]) && open == 'e')
		return (exp_string(mns, str, i));
	while (str[*i])
	{
		if ((!ft_isalnum(str[*i]) && str[*i] != '_')
			|| str[*i] == '?')
			break ;
		(*i)++;
	}
	if (str[*i] == '?' && str[*i - 1] == '$')
		(*i)++;
	key = ft_substr(str, start, *i - start);
	if (!key)
		ft_bad_alloc(mns);
	return (key);
}

void	exp_check_open(char c, char *open)
{
	if (c == '\'' || c == '\"')
	{
		if (*open == c)
			*open = 'e';
		else if (*open == 'e')
			*open = c;
	}
}
