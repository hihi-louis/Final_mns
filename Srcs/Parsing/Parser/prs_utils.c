/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:42:09 by tripham           #+#    #+#             */
/*   Updated: 2025/04/26 02:34:54 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prs_rd_ambi(t_shell *mns, t_cmd *gr, t_token *lst, int *k)
{
	gr->final[*k].val = ft_strdup(lst->val);
	if (!gr->final[*k].val)
		ft_bad_alloc(mns);
	gr->final[*k].type = lst->type;
	(*k)++;
}
