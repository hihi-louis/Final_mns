/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:56:17 by tripham           #+#    #+#             */
/*   Updated: 2025/04/14 18:42:17 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_clean_all(t_ast *ast)
{
	if (!ast)
		return ;
	ast_clean_all(ast->left);
	ast_clean_all(ast->right);
	free(ast);
}
