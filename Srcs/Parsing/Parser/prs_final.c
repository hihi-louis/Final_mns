/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_final.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:23:02 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/22 22:15:25 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prs_init(t_type *a, t_type *b)
{
	*a = *b;
}

static int	prs_val_count(char *input)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (input[i])
	{
		if (ft_isallspace(input[i]))
			i = prs_skip_space(input, i);
		else
		{
			cnt++;
			i = prs_skip_word(input, i);
		}
	}
	return (cnt);
}

static void	prs_final_count(t_cmd *group, t_token *list)
{
	int	i;

	i = 0;
	while (i < group->token_cnt)
	{
		if (list[i].type == RD_AMBI)
			group->final_cnt++;
		else if (list[i].type != SIGN)
			group->final_cnt += prs_val_count(list[i].exp);
		i++;
	}
}

static void	prs_final_split(t_shell *mns, t_cmd *gr, t_token *lst, int *k)
{
	int		i;
	char	**res;

	i = 0;
	res = prs_split_allspace(lst->exp);
	if (!res)
		ft_bad_alloc(mns);
	while (i < ft_2d_len(res))
	{
		if (lst->exp && lst->exp[0])
		{
			gr->final[*k].val = ft_strdup(res[i]);
			if (!gr->final[*k].val)
				ft_bad_alloc(mns);
			gr->final[*k].type = lst->type;
			(*k)++;
		}
		i++;
	}
	ft_free_2d((void **)res);
}

void	prs_final(t_shell *mns, int i, int j, int k)
{
	while (++i < mns->group_cnt)
	{
		k = 0;
		prs_final_count(&mns->cmd_group[i], mns->cmd_group[i].list);
		mns->cmd_group[i].final = malloc(mns->cmd_group[i].final_cnt
				* sizeof(t_token));
		if (!mns->cmd_group[i].final)
			ft_bad_alloc(mns);
		ft_bzero(mns->cmd_group[i].final,
			mns->cmd_group[i].final_cnt * sizeof(t_token));
		j = -1;
		while (++j < mns->cmd_group[i].token_cnt
			&& k < mns->cmd_group[i].final_cnt)
		{
			if (mns->cmd_group[i].list[j].type == RD_AMBI)
				prs_rd_ambi(mns, &mns->cmd_group[i],
					&mns->cmd_group[i].list[j], &k);
			else if (mns->cmd_group[i].list[j].type != SIGN)
				prs_final_split(mns, &mns->cmd_group[i],
					&mns->cmd_group[i].list[j], &k);
			else
				prs_init(&mns->cmd_group[i].final[k].type,
					&mns->cmd_group[i].list[j].type);
		}
	}
}
