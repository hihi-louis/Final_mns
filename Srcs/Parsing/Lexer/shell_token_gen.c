/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_token_gen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:45:13 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/26 00:47:15 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lx_cmd_group(t_shell *mns)
{
	int	i;

	i = 0;
	while (i < mns->group_cnt)
	{
		lx_cmd_group_gen(mns, mns->cmd_group[i].final, &mns->cmd_group[i]);
		i++;
	}
}

static void	lx_typize_token(t_shell *mns, t_token *list, char **str, int size)
{
	t_point	p;

	p.start = -1;
	p.end = size;
	while (++p.start < size)
	{
		if (lx_is_rd(str[p.start]))
			lx_rd_typize(mns, list, str, &p);
		else
		{
			list[p.start].type = ARG;
			list[p.start].val = ft_strdup(str[p.start]);
			if (!list[p.start].val)
				ft_bad_alloc(mns);
		}
	}
}

static void	lx_token_listing(t_shell *mns)
{
	int	i;

	i = 0;
	while (i < mns->group_cnt)
	{
		mns->cmd_group[i].list = malloc(mns->cmd_group[i].token_cnt
				* sizeof(t_token));
		if (!mns->cmd_group[i].list)
			ft_bad_alloc(mns);
		ft_bzero(mns->cmd_group[i].list,
			mns->cmd_group[i].token_cnt * sizeof(t_token));
		i++;
	}
	i = 0;
	while (i < mns->group_cnt)
	{
		lx_typize_token(mns, mns->cmd_group[i].list, mns->cmd_group[i].token,
			mns->cmd_group[i].token_cnt);
		i++;
	}
	prs_list_check(mns);
}

void	shell_token_gen(t_shell *mns, char *input, int i)
{
	mns->cmd_str = lx_group_split(mns, input);
	if (!mns->cmd_str)
		ft_bad_alloc(mns);
	mns->cmd_group = malloc(mns->group_cnt * sizeof(t_cmd));
	if (!mns->cmd_group)
		ft_bad_alloc(mns);
	while (++i < mns->group_cnt)
		ft_bzero(&mns->cmd_group[i], sizeof(t_cmd));
	i = -1;
	while (++i < mns->group_cnt)
	{
		mns->cmd_group[i].token = lx_token_split(mns, mns->cmd_str[i], i);
		if (!mns->cmd_group[i].token)
			ft_bad_alloc(mns);
	}
	lx_token_listing(mns);
	if (mns->shell_err == -3)
		return ;
	exp_group_generate(mns);
	prs_final(mns, -1, -1, 0);
	lx_cmd_group(mns);
}
