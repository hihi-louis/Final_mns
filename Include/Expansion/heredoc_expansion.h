/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:11:28 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/21 04:21:10 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_EXPANSION_H

# define HEREDOC_EXPANSION_H

# include "minishell.h"

typedef struct s_shell	t_shell;
typedef struct s_point	t_point;

void	hd_expansion_gen(t_shell *mns, char **line);
void	hd_expand(t_shell *mns, char **temp, char **key);
void	hd_expand_digit(t_shell *mns, char **key, char **temp);
char	*hd_getkey(t_shell *mns, char *line, int *i);

#endif