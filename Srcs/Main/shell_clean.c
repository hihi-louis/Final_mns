/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:24:53 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/22 11:50:12 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_list(t_token *list, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (list[i].val)
			free(list[i].val);
		if (list[i].exp)
			free(list[i].exp);
		i++;
	}
	free(list);
}

static void	free_cmd_group(t_cmd *group, int id)
{
	if (group[id].list)
		free_list(group[id].list, group[id].token_cnt);
	if (group[id].cmd_arg)
		ft_free_2d((void **)group[id].cmd_arg);
	if (group[id].token)
		ft_free_2d((void **)group[id].token);
	if (group[id].heredoc)
		ft_free_2d((void **)group[id].heredoc);
	if (group[id].out)
		free_out(group, id);
	if (group[id].in)
		free_in(group, id);
	if (group[id].ambi)
		free(group[id].ambi);
	if (group[id].final)
		free_list(group[id].final, group[id].final_cnt);
}

static void	free_group(t_cmd *group, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free_cmd_group(group, i);
		i++;
	}
	free(group);
}

void	shell_pre_input(t_shell *mns)
{
	if (!mns)
		return ;
	if (mns->ast)
	{
		ast_clean_all(mns->ast);
		mns->ast = NULL;
	}
	if (mns->full_cmd_line)
	{
		free(mns->full_cmd_line);
		mns->full_cmd_line = NULL;
	}
	if (mns->cmd_str)
	{
		ft_free_2d((void **)mns->cmd_str);
		mns->cmd_str = NULL;
	}
	if (mns->cmd_group)
	{
		free_group(mns->cmd_group, mns->group_cnt);
		mns->cmd_group = NULL;
	}
}

void	shell_clean(t_shell *mns)
{
	if (!mns)
		return ;
	if (mns->full_cmd_line)
	{
		free(mns->full_cmd_line);
		mns->full_cmd_line = NULL;
	}
	if (mns->cmd_str)
	{
		ft_free_2d((void **)mns->cmd_str);
		mns->cmd_str = NULL;
	}
	if (mns->ast)
	{
		ast_clean_all(mns->ast);
		mns->ast = NULL;
	}
	if (mns->cmd_group)
	{
		free_group(mns->cmd_group, mns->group_cnt);
		mns->cmd_group = NULL;
	}
	if (mns->env)
		ft_free_2d((void **)mns->env);
	free(mns);
}
