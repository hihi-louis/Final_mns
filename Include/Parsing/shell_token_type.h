/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_token_type.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 01:28:19 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/22 11:08:08 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TOKEN_TYPE_H

# define SHELL_TOKEN_TYPE_H
# include "../Main/minishell.h"

typedef enum s_type
{
	ARG,
	SIGN,
	SIGN_ERR,
	RD_IN,
	RD_OUT,
	RD_APPEND,
	RD_HEREDOC,
	RD_AMBI
}	t_type;

typedef struct s_rd
{
	t_type	type;
	char	*val;
}	t_rd;
typedef struct s_token
{
	t_type	type;
	char	*val;
	char	*exp;
}	t_token;

typedef struct s_cmd
{
	int		token_cnt;
	int		ambi_cnt;
	int		final_cnt;
	char	**token;
	t_token	*list;
	t_token	*final;
	int		arg_cnt;
	int		out_cnt;
	int		in_cnt;
	int		heredoc_cnt;
	char	*ambi;
	char	**cmd_arg;
	t_token	*in;
	t_token	*out;
	char	**heredoc;
}	t_cmd;

#endif