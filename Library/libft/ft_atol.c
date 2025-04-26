/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:08:53 by tripham           #+#    #+#             */
/*   Updated: 2025/04/18 21:29:58 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_parse_digits(const char *s, long *out, int i, int sign)
{
	long	r;

	r = 0;
	while (ft_isdigit(s[i]))
	{
		if (r > (LONG_MAX - (s[i] - '0')) / 10)
			return (0);
		r = r * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] != '\0')
		return (0);
	*out = r * sign;
	return (1);
}

int	ft_atol_safe(const char *s, long *out)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	*out = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(s[i]))
		return (0);
	return (ft_parse_digits(s, out, i, sign));
}
