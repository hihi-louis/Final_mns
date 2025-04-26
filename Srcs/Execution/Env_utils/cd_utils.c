/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 04:39:28 by tripham           #+#    #+#             */
/*   Updated: 2025/04/20 17:27:02 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_env_var(const char *env, const char *key)
{
	size_t	val_len;
	size_t	key_len;
	char	*env_var;

	val_len = ft_strlen(env);
	key_len = ft_strlen(key);
	env_var = malloc(sizeof(char) * (val_len + key_len + 2));
	if (!env_var)
		return (NULL);
	ft_memcpy(env_var, key, key_len);
	env_var[key_len] = '=';
	ft_memcpy(env_var + key_len + 1, env, val_len);
	env_var[val_len + key_len + 1] = '\0';
	return (env_var);
}

static int	cpy_add_env(char ***env, char *env_var, size_t i)
{
	char	**new_env;
	size_t	j;

	j = 0;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (free(env_var), 1);
	while (j < i)
	{
		new_env[j] = (*env)[j];
		j++;
	}
	new_env[i] = env_var;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	set_env_val(char ***env, const char *key, const char *value)
{
	char	*env_var;
	size_t	i;

	i = 0;
	env_var = create_env_var(value, key);
	if (!env_var)
		return (1);
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, ft_strlen(key))
			&& (*env)[i][ft_strlen(key)] == '=')
		{
			free((*env)[i]);
			(*env)[i] = env_var;
			return (0);
		}
		i++;
	}
	return (cpy_add_env(env, env_var, i));
}

char	*get_env_val(t_shell *mns, char *key)
{
	int	i;

	i = 0;
	if (!mns || !mns->env || !key || !key[0])
		return (NULL);
	while (mns->env[i])
	{
		if (mns->env[i][0] && ft_strncmp(mns->env[i],
			key, ft_strlen(key)) == 0 && mns->env[i][ft_strlen(key)] == '=')
			return (mns->env[i] + ft_strlen(key) + 1);
		i++;
	}
	return (NULL);
}

char	*expand_titled(t_shell *mns, char *arg)
{
	char	*home;
	char	*expanded;

	if (!arg || arg[0] != '~')
		return (arg);
	if (arg[1] == '\0' || arg[1] == '/')
	{
		home = get_env_val(mns, "HOME");
		if (!home)
			return (arg);
		expanded = ft_strjoin(home, arg + 1);
		if (!expanded)
			return (arg);
		return (expanded);
	}
	return (arg);
}
