/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 02:02:44 by caonguye          #+#    #+#             */
/*   Updated: 2025/03/14 10:50:41 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	lend;
	size_t	lens;
	size_t	j;

	if ((!dst || !src) && len == 0)
		return (0);
	lend = ft_strlen(dst);
	lens = ft_strlen(src);
	j = 0;
	if (lend >= len)
		return (lens + len);
	while (lend + j < len - 1 && src[j])
	{
		dst[lend + j] = src[j];
		j++;
	}
	dst[lend + j] = '\0';
	return (lend + lens);
}
