/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ep_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:39:38 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/20 21:57:24 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ep_option(t_shell *mns, char *str, int err)
{
	ft_printf_fd(2, "bash: export: '%c%c': not a valid identifier\n",
		str[0], str[1]);
	ft_printf_fd(2,
		"export: usage: export [-fn] [name[=value] ...] or export -p\n");
	update_status(mns, 2);
	return (err);
}

int	ep_check_exist(t_shell *mns, char *str, char ***res)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(str, "=");
	if (!temp)
	{
		ft_free_3d((void ***)res);
		ft_bad_alloc(mns);
	}
	i = ep_exist(mns, temp);
	free(temp);
	return (i);
}

int	ep_exist(t_shell *mns, char *str)
{
	int	i;
	int	size;
	int	len;

	i = 0;
	size = ft_2d_len(mns->env);
	len = ft_strichr(str, '=');
	while (i < size)
	{
		if (len > -1 && !ft_strncmp(mns->env[i], str, len + 1))
			return (i);
		i++;
	}
	return (-1);
}

int	ep_validation(t_shell *mns, char *str, int i, int size)
{
	int	err;

	err = 1;
	while (i < size && err != 0)
	{
		if (str[0] == '-')
			return (ep_option(mns, str, 0));
		if (i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
			err = 0;
		else if (i > 0 && !ft_isalnum(str[i]) && str[i] != '_')
			err = 0;
		i++;
	}
	if ((err == 0 || (i == 0 && str[i] == '=')))
	{
		ft_printf_fd(2, "bash: export: `%s': not a valid identifier\n", str);
		update_status(mns, 1);
		return (err);
	}
	return (1);
}

int	ep_pre_validation(t_shell *mns, char **var)
{
	int	check;

	if ((!var[0] || !var[0][0]) && var[1])
	{
		check = ep_validation(mns, var[1], 0, ft_strlen(var[1]));
		if (!check)
			ft_free_2d((void **)var);
		return (check);
	}
	else
	{
		check = ep_validation(mns, var[0], 0, ft_strlen(var[0]));
		if (!check)
			ft_free_2d((void **)var);
		return (check);
	}
}
