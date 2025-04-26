/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_cnt_2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:09:44 by caonguye          #+#    #+#             */
/*   Updated: 2025/01/14 19:11:28 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_cnt_2d(char *src, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (src[i])
	{
		if (src[i] == c)
			cnt++;
		i++;
	}
	return (cnt);
}
