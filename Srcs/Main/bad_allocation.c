/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:30:41 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/13 21:51:49 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bad_alloc(t_shell *mns)
{
	printf("minishell: bad allocation\n");
	shell_clean(mns);
	exit(EXIT_FAILURE);
}
