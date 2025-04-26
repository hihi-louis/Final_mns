/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 07:58:40 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/22 23:14:34 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp_unstring(t_shell *mns, char **key)
{
	char	*str;

	str = ft_strdup(*key);
	if (!str)
	{
		free(*key);
		ft_bad_alloc(mns);
	}
	if (str && ft_strlen(str) > 0)
	{
		if (!ft_append(&mns->post_expansion, &str))
		{
			free(*key);
			ft_bad_alloc(mns);
		}
	}
	hd_expansion_gen(mns, &mns->post_expansion);
	free(*key);
}

void	exp_type(t_shell *mns, char **key, char open, t_token *t)
{
	if (ft_is_dquote(key[0][0]))
		exp_unstring(mns, key);
	else
		exp_expand(mns, key, open, t);
}
