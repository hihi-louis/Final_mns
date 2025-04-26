/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:56:11 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/18 17:35:03 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_append_2d(char ***s1, char *s2)
{
	int		i;
	int		size;
	char	**temp;

	i = -1;
	size = ft_2d_len(*s1);
	temp = malloc((size + 2) * sizeof(char *));
	if (!temp)
		return (0);
	while (++i < size)
		temp[i] = ft_strdup((*s1)[i]);
	temp[i] = ft_strdup(s2);
	if (!temp[i])
		return (0);
	temp[i + 1] = NULL;
	ft_free_2d((void **)(*s1));
	*s1 = temp;
	return (1);
}
