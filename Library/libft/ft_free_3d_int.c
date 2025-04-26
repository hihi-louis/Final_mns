/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_3d_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:32:04 by caonguye          #+#    #+#             */
/*   Updated: 2025/03/13 01:47:05 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_3d_int(int ***arr, int len)
{
	if (!*arr)
		return ;
	ft_free_2d_int(*arr, len);
	*arr = NULL;
}
