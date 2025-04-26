/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_process_2d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 02:38:00 by caonguye          #+#    #+#             */
/*   Updated: 2025/03/14 10:50:41 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_process_2d(char **arr, size_t cur)
{
	if (!arr[cur])
	{
		while (cur-- > 0)
		{
			free(arr[cur]);
			arr[cur] = NULL;
		}
		free(arr);
		arr = NULL;
		return (0);
	}
	return (1);
}
