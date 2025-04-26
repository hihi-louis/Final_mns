/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:40:48 by tripham           #+#    #+#             */
/*   Updated: 2025/04/26 17:32:36 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_shell	t_shell;
typedef struct s_token	t_token;

typedef enum e_ast_type
{
	NODE_CMD,
	NODE_PIPE
}	t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	t_token			*cmd_tokens;
	int				cmd_index;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// AST
t_ast	*create_ast_node_cmd(t_shell *mns, t_token *tokens, int index);
t_ast	*create_ast_node_pipe(void);
t_ast	*ast_init(t_shell *mns, t_cmd *cmd_group,
			int group_cnt, int base_index);
#endif
