/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ep_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:22:21 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/24 10:42:33 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ep_replace(t_shell *mns, char *str, int i)
{
	if (!mns->env || !mns->env[0] || !str)
		ft_bad_alloc(mns);
	if (mns->env[i])
		free(mns->env[i]);
	if (!str[0])
		mns->env[i] = ft_strdup("");
	else
		mns->env[i] = ft_strdup(str);
	if (!mns->env[i])
		ft_bad_alloc(mns);
}

static void	ep_print(char *env, int pos, int len)
{
	int	j;

	if (pos == -1)
		printf("declare -x %s\n", env);
	else
	{
		printf("declare -x ");
		j = -1;
		while (++j < len)
		{
			if (j == pos + 1)
				printf("\"");
			printf("%c", env[j]);
		}
		printf("\"\n");
	}
}

void	ep_standalone(t_shell *mns, int i, int size)
{
	int		pos;
	int		len;
	char	**sorted_env;

	sorted_env = env_sorting(mns);
	if (!sorted_env)
		ft_bad_alloc(mns);
	while (++i < size)
	{
		printf("HERE");
		if (sorted_env[i][0] == '_')
			continue ;
		pos = ft_strichr(sorted_env[i], '=');
		len = ft_strlen(sorted_env[i]);
		ep_print(sorted_env[i], pos, len);
	}
	ft_free_2d((void **)sorted_env);
}
