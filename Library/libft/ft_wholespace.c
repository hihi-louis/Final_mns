/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wholespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:38:40 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/03 02:19:38 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wholespace(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	if (i == size)
		return (1);
	while (i < size)
	{
		if (ft_isallspace(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
