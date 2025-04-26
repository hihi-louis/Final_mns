/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:25:18 by caonguye          #+#    #+#             */
/*   Updated: 2025/03/14 10:50:41 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t len)
{
	void	*res;

	if (nmemb * len == 0)
		return (malloc(0));
	if (nmemb != (nmemb * len / len))
		return (NULL);
	res = malloc(len * nmemb);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, nmemb * len);
	return (res);
}
