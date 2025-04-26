/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_ft.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:22:16 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/22 23:13:31 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_FT_H

# define SHELL_ENV_FT_H

//STRUCT FORWARD DECLARATION
typedef struct s_shell	t_shell;

typedef struct s_sort
{
	int	i;
	int	j;
	int	k;
	int	id;
	int	ls;
	int	rs;
}	t_sort;

typedef struct s_point
{
	int	start;
	int	end;
}	t_point;

char	**env_sorting(t_shell *mns);
int		merge_sort(char **env, int left, int right);
void	env_shlvl_gen(t_shell *mns);
void	env_shlvl_up(t_shell *mns);
void	env_shlvl_down(t_shell *mns);

//EXPANSION
int		exp_validation(char *key);
//int		exp_rd_check(t_shell *mns, t_token *t, char *key, char open);
void	exp_generate(t_shell *mns, int i, int j);
void	exp_group_generate(t_shell *mns);
void	exp_check_open(char c, char *open);
char	*exp_getkey(t_shell *mns, char *str, int *i, char open);
char	*exp_new_strdup(const char *s);
void	exp_expand(t_shell *mns, char **key, char open, t_token *t);
void	exp_type(t_shell *mns, char **key, char open, t_token *t);

#endif