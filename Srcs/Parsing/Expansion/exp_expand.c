/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:56:48 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/22 23:12:02 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp_expand_new(t_shell *mns, char **key, char *exp_sign)
{
	char	*str;

	if (ft_strcmp(*key, "?") && !get_env_val(mns, *key))
		return (free(*key), free(exp_sign));
	if (!ft_strcmp(*key, "?"))
		str = ft_itoa(mns->exitcode);
	else
		str = exp_new_strdup(get_env_val(mns, *key));
	if (!str)
		ft_bad_alloc(mns);
	if (str && ft_strlen(str) > 0)
	{
		if (!ft_append(&mns->post_expansion, &str))
		{
			free(*key);
			free(exp_sign);
			ft_bad_alloc(mns);
		}
	}
	else
		free(str);
	return (free(*key), free(exp_sign));
}

static void	exp_expand_digit(t_shell *mns, char **key, char *exp_sign)
{
	char	*temp;

	temp = ft_strdup(*key + 1);
	if (!ft_append(&mns->post_expansion, &temp))
	{
		free(*key);
		free(exp_sign);
		ft_bad_alloc(mns);
	}
	free(*key);
	free(exp_sign);
}

static void	exp_expand_org(t_shell *mns, char **key, char *exp_sign)
{
	char	*str;

	if (ft_strcmp(*key, "?") && !get_env_val(mns, *key))
	{
		free(*key);
		free(exp_sign);
		return ;
	}
	if (!ft_strcmp(*key, "?"))
		str = ft_itoa(mns->exitcode);
	else
		str = ft_strdup(get_env_val(mns, *key));
	if (!str)
		ft_bad_alloc(mns);
	if (str && ft_strlen(str) > 0)
	{
		if (!ft_append(&mns->post_expansion, &str))
		{
			free(*key);
			free(exp_sign);
			ft_bad_alloc(mns);
		}
	}
	free(*key);
	free(exp_sign);
}

static void	exp_copy(t_shell *mns, char **key, char *exp_sign)
{
	if (!ft_append(&mns->post_expansion, &exp_sign))
	{
		free(*key);
		ft_bad_alloc(mns);
	}
	if (!ft_append(&mns->post_expansion, key))
		ft_bad_alloc(mns);
}

void	exp_expand(t_shell *mns, char **key, char open, t_token *t)
{
	int		type;
	char	*exp_sign;

	type = exp_validation(*key);
	exp_sign = ft_strdup("$");
	if (!exp_sign)
	{
		free(*key);
		ft_bad_alloc(mns);
	}
	if (open == '\'' || t->type == RD_HEREDOC)
		exp_copy(mns, key, exp_sign);
	else
	{
		if (type == 1)
			exp_expand_digit(mns, key, exp_sign);
		else
		{
			if (open == '\"')
				exp_expand_org(mns, key, exp_sign);
			else
				exp_expand_new(mns, key, exp_sign);
		}
	}
}
