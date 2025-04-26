/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:45:20 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/20 17:39:42 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_shlvl_gen(t_shell *mns)
{
	int		pos;
	char	*shlvl;
	char	*new;

	shlvl = ft_itoa(mns->shlvl);
	pos = ep_exist(mns, "SHLVL=");
	new = ft_strjoin("SHLVL=", shlvl);
	if (!new)
		ft_bad_alloc(mns);
	if (pos != -1)
		ep_replace(mns, new, pos);
	else
		env_append(mns, new);
	free(shlvl);
	free(new);
}

void	env_shlvl_up(t_shell *mns)
{
	char	*shlvl;

	shlvl = get_env_val(mns, "SHLVL");
	if (shlvl == NULL)
	{
		mns->shlvl = 1;
		env_shlvl_gen(mns);
	}
	else
	{
		mns->shlvl = ft_atoi(shlvl) + 1;
		env_shlvl_gen(mns);
	}
}

void	env_shlvl_down(t_shell *mns)
{
	char	*shlvl;

	shlvl = get_env_val(mns, "SHLVL");
	if (!ft_strcmp(shlvl, "1"))
	{
		mns->shlvl = 0;
		unset_env_var("SHLVL", &mns->env);
	}
	else
	{
		mns->shlvl = ft_atoi(shlvl) - 1;
		env_shlvl_gen(mns);
	}
}
