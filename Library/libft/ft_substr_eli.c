/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_eli.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 04:05:40 by caonguye          #+#    #+#             */
/*   Updated: 2025/03/17 12:28:44 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_eli(char *s, int start, int len, char c)
{
	char	*res;
	int		i;
	int		lens;

	i = 0;
	lens = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= lens)
		return (ft_strdup(""));
	if (len > lens - start)
		len = lens - start;
	res = malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (i < len && s[start])
	{
		while (s[start] == c)
			start++;
		res[i++] = s[start++];
	}
	res[i] = '\0';
	return (res);
}
