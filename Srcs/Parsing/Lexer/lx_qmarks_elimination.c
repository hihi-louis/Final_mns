/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_qmarks_elimination.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:49:26 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/21 13:05:29 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lx_qmarks_cnt(char *str)
{
	int		i;
	int		cnt;
	char	sign;

	sign = 'e';
	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (ft_is_dquote(str[i]) && sign == 'e')
			sign = str[i];
		else if (str[i] == sign && sign != 'e')
			sign = 'e';
		else
			cnt++;
		i++;
	}
	return (cnt);
}

char	*lx_qmarks_eli(t_shell *mns, char *str, int i, int j)
{
	int		size;
	char	sign;
	char	*res;

	sign = 'e';
	size = lx_qmarks_cnt(str);
	res = malloc(size + 1);
	if (!res)
		ft_bad_alloc(mns);
	while (str[i])
	{
		if (ft_is_dquote(str[i]) && sign == 'e')
			sign = str[i];
		else if (str[i] == sign && sign != 'e')
			sign = 'e';
		else
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[size] = '\0';
	return (res);
}
