/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_generate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 00:35:59 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/23 11:03:30 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exp_condition(t_token *str, int size, int i, char open)
{
	if ((i + 1 < size && str->val[i] == '$' && (ft_isalnum(str->val[i + 1])
				|| str->val[i + 1] == '_' || str->val[i + 1] == '?'))
		|| (i + 1 < size && str->val[i] == '$'
			&& ft_is_dquote(str->val[i + 1]) && open == 'e'))
		return (1);
	return (0);
}

static void	exp_subjoin(t_shell *mns, t_point p, char *str)
{
	char	*temp;

	temp = ft_substr(str, p.start, p.end - p.start);
	if (!temp)
	{
		free(mns->post_expansion);
		ft_bad_alloc(mns);
	}
	if (!ft_append(&mns->post_expansion, &temp))
		ft_bad_alloc(mns);
}

static void	exp_check(t_shell *mns, t_token *str, int size, int i)
{
	t_point		p;
	char		open;
	char		*key;

	ft_bzero(&p, sizeof(t_point));
	open = 'e';
	while (i < size)
	{
		exp_check_open(str->val[i], &open);
		if (exp_condition(str, size, i, open))
		{
			p.end = i;
			exp_subjoin(mns, p, str->val);
			key = exp_getkey(mns, str->val, &i, open);
			p.start = i;
			exp_type(mns, &key, open, str);
		}
		else
			i++;
	}
	p.end = i;
	if (p.start != p.end)
		exp_subjoin(mns, p, str->val);
}

void	exp_generate(t_shell *mns, int i, int j)
{
	while (++j < mns->cmd_group[i].token_cnt)
	{
		mns->post_expansion = ft_strdup("");
		if (!mns->post_expansion)
			ft_bad_alloc(mns);
		if (mns->cmd_group[i].list[j].type == SIGN
			|| mns->cmd_group[i].list[j].type == SIGN_ERR)
		{
			free(mns->post_expansion);
			mns->post_expansion = NULL;
			continue ;
		}
		exp_check(mns, &mns->cmd_group[i].list[j],
			ft_strlen(mns->cmd_group[i].list[j].val), 0);
		mns->cmd_group[i].list[j].exp = ft_strdup(mns->post_expansion);
		if (!mns->cmd_group[i].list[j].exp)
		{
			free(mns->post_expansion);
			ft_bad_alloc(mns);
		}
		free(mns->post_expansion);
		mns->post_expansion = NULL;
	}
}

void	exp_group_generate(t_shell *mns)
{
	int	i;
	int	j;

	i = 0;
	while (i < mns->group_cnt)
	{
		exp_generate(mns, i, -1);
		i++;
	}
	i = -1;
	while (++i < mns->group_cnt)
	{
		j = -1;
		while (++j < mns->cmd_group[i].token_cnt)
		{
			if (mns->cmd_group[i].list[j].type > SIGN_ERR
				&& mns->cmd_group[i].list[j].type > SIGN_ERR
				&& (!mns->cmd_group[i].list[j].exp[0]
					|| ft_wholespace(mns->cmd_group[i].list[j].exp)))
				mns->cmd_group[i].list[j].type = RD_AMBI;
		}
	}
}
