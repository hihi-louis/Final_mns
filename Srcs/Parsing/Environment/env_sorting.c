/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sorting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:53:29 by caonguye          #+#    #+#             */
/*   Updated: 2025/03/23 23:21:19 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_right(char **env, char **right, t_sort *id)
{
	while (id->j < id-> rs)
	{
		if (right[id->j])
		{
			if (env[id->k])
				free(env[id->k]);
			env[id->k] = ft_strdup(right[id->j]);
			if (!env[id->k])
				return (ft_free_process_2d(env, id->k));
		}
		else
			env[id->k] = NULL;
		id->k++;
		id->j++;
	}
	return (1);
}

static int	fill_left(char **env, char **left, t_sort *id)
{
	while (id->i < id->ls)
	{
		if (left[id->i])
		{
			if (env[id->k])
				free(env[id->k]);
			env[id->k] = ft_strdup(left[id->i]);
			if (!env[id->k])
				return (ft_free_process_2d(env, id->k));
		}
		else
			env[id->k] = NULL;
		id->i++;
		id->k++;
	}
	return (1);
}

static int	merge(char **env, char **left, char **right, t_sort *id)
{
	id->i = 0;
	id->j = 0;
	while (right[id->j] && left[id->i]
		&& id->i < id->ls && id->j < id->rs)
	{
		if (ft_strcmp(left[id->i], right[id->j]) <= 0)
		{
			if (env[id->k])
				free(env[id->k]);
			env[id->k++] = ft_strdup(left[id->i++]);
			if (!env[id->k])
				return (ft_free_process_2d(env, id->k));
		}
		else
		{
			if (env[id->k])
				free(env[id->k]);
			env[id->k++] = ft_strdup(right[id->j++]);
			if (!env[id->k - 1])
				return (ft_free_process_2d(env, --id->k));
		}
	}
	fill_left(env, left, id);
	fill_right(env, right, id);
	return (1);
}

static int	merge_set_up(char **env, int l, int mid, int r)
{
	t_sort	id;
	char	**left;
	char	**right;

	ft_bzero(&id, sizeof(id));
	left = (char **)malloc((mid - l + 2) * sizeof(char *));
	if (!left)
		return (0);
	right = (char **)malloc((r - mid + 1) * sizeof(char *));
	if (!right)
	{
		ft_free_2d((void **)left);
		return (0);
	}
	if (!ft_sub_2d(env, left, l, mid - l + 1)
		|| !ft_sub_2d(env, right, mid + 1, r - mid))
		return (0);
	id.ls = mid - l + 1;
	id.rs = r - mid;
	id.k = l;
	if (!merge(env, left, right, &id))
		return (0);
	ft_free_2d((void **)left);
	ft_free_2d((void **)right);
	return (1);
}

int	merge_sort(char **env, int left, int right)
{
	int	mid;

	if (left < right)
	{
		mid = (left + right) / 2;
		if (!merge_sort(env, left, mid))
			return (0);
		if (!merge_sort(env, mid + 1, right))
			return (0);
		if (!merge_set_up(env, left, mid, right))
			return (0);
	}
	return (1);
}
