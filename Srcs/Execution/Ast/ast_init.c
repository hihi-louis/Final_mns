/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:58:02 by tripham           #+#    #+#             */
/*   Updated: 2025/04/28 02:13:58 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_ast_node_cmd(t_shell *mns, t_token *tokens, int index)
{
	t_ast	*node;

	(void)mns;
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->cmd_tokens = tokens;
	node->cmd_index = index;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*create_ast_node_pipe(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->cmd_tokens = NULL;
	node->cmd_index = -1;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*ast_init(t_shell *mns, t_cmd *cmd_group, int group_cnt, int base_index)
{
	t_ast	*pipe_node;

	if (group_cnt == 0)
		return (NULL);
	if (group_cnt == 1)
		return (create_ast_node_cmd(mns, cmd_group[0].final, base_index));
	pipe_node = create_ast_node_pipe();
	pipe_node->left = create_ast_node_cmd(mns, cmd_group[0].final, base_index);
	pipe_node->right = ast_init(mns, cmd_group + 1,
			group_cnt - 1, base_index + 1);
	return (pipe_node);
}
