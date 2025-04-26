/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:26:37 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/26 18:29:29 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "system_lib.h"
# include "error.h"
# include "../../Library/libft/libft.h"
# include "../../Library/ft_printf_fd/ft_printf.h"
# include "../Parsing/shell_token_type.h"
# include "../Parsing/shell_token_ft.h"
# include "../Parsing/shell_env_ft.h"
# include "../Execution/ast.h"
# include "../Execution/execution.h"
# include "../Execution/builtin_functions.h"
# include "../Expansion/heredoc_expansion.h"
# include "../Expansion/unstring_expansion.h"

typedef struct s_shell
{
	int		group_cnt;
	int		exitcode;
	int		shlvl;
	int		signal;
	char	*full_cmd_line;
	char	*post_expansion;
	char	**cmd_str;
	char	**env;
	t_cmd	*cmd_group;
	int		shell_err;
	t_ast	*ast;
	int		std_fd[2];
	bool	is_pipe;
	int		heredoc_failed;
}	t_shell;

//OPERATION
int		shell_init(t_shell *mns, char **env);
void	shell_pre_input(t_shell *mns);
int		shell_implement(char **env);
void	shell_clean(t_shell *mns);
void	free_out(t_cmd *group, int id);
void	free_in(t_cmd *group, int id);
void	shell_env_gen(t_shell *mns, char **env);

//PARSING
void	shell_input(t_shell	*mns);
void	shell_token_gen(t_shell *mns, char *input, int i);

//ERROR HANDLING
void	ft_bad_alloc(t_shell *mns);

#endif