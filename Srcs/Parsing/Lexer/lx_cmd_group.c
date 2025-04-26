/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_cmd_group.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:47:55 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/22 11:41:21 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lx_out_hd_cnt(t_token *final, t_cmd *group)
{
	int	i;

	i = 0;
	while (i < group->final_cnt)
	{
		if (final[i].type == RD_OUT || final[i].type == RD_APPEND)
			group->out_cnt++;
		else if (final[i].type == RD_IN || final[i].type == RD_HEREDOC
			|| final[i].type == RD_AMBI)
		{
			if (final[i].type == RD_HEREDOC)
				group->heredoc_cnt++;
			group->in_cnt++;
		}
		else if (final[i].type == ARG)
			group->arg_cnt++;
		i++;
	}
}

static void	lx_in_file(t_shell *mns, t_token *final, t_cmd *group, t_sort *id)
{
	group->in[id->ls].val = lx_qmarks_eli(mns, final[id->id].val, 0, 0);
	group->in[id->ls++].type = final[id->id].type;
	if (final[id->id].type == RD_HEREDOC)
	{
		group->heredoc[id->k] = ft_strdup(final[id->id].val);
		if (!group->heredoc[id->k++])
			ft_bad_alloc(mns);
	}
}

static void	lx_out_file(t_shell *mns, t_token *final, t_cmd *group, t_sort *id)
{
	group->out[id->j].val = lx_qmarks_eli(mns, final[id->id].val, 0, 0);
	group->out[id->j++].type = final[id->id].type;
}

static void	lx_group_copy(t_shell *mns, t_token *final, t_cmd *gr, t_sort *id)
{
	while (++id->id < gr->final_cnt)
	{
		if (final[id->id].type == ARG)
		{
			gr->cmd_arg[id->i++] = lx_qmarks_eli(mns,
					final[id->id].val, 0, 0);
		}
		else if (final[id->id].type == RD_IN
			|| final[id->id].type == RD_HEREDOC
			|| final[id->id].type == RD_AMBI)
			lx_in_file(mns, final, gr, id);
		else if (final[id->id].type == RD_OUT
			|| final[id->id].type == RD_APPEND)
			lx_out_file(mns, final, gr, id);
	}
}

void	lx_cmd_group_gen(t_shell *mns, t_token *final, t_cmd *group)
{
	t_sort	id;

	ft_bzero(&id, sizeof(id));
	id.id = -1;
	lx_out_hd_cnt(final, group);
	group->out = malloc(group->out_cnt * sizeof(t_token));
	if (!group->out)
		ft_bad_alloc(mns);
	group->heredoc = malloc((group->heredoc_cnt + 1) * sizeof(char *));
	if (!group->heredoc)
		ft_bad_alloc(mns);
	group->cmd_arg = malloc((group->arg_cnt + 1) * sizeof(char *));
	if (!group->cmd_arg)
		ft_bad_alloc(mns);
	group->in = malloc(group->in_cnt * sizeof(t_token));
	if (!group->in)
		ft_bad_alloc(mns);
	lx_group_copy(mns, final, group, &id);
	group->heredoc[group->heredoc_cnt] = NULL;
	group->cmd_arg[group->arg_cnt] = NULL;
}
