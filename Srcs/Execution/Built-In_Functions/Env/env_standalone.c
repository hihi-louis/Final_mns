/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_standalone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 04:12:53 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/24 03:50:17 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_standalone(t_shell *mns)
{
	int	i;
	int	size;

	i = 0;
	size = ft_2d_len(mns->env);
	while (i < size)
	{
		if (ft_strichr(mns->env[i], '=') != -1)
			printf("%s\n", mns->env[i]);
		i++;
	}
}
