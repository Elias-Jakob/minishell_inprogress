/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:47:19 by leberton          #+#    #+#             */
/*   Updated: 2025/04/27 23:13:16 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
	c == '\v' || c == '\f' || c == '\r');
}

static int	ft_isplus_isminus(int c)
{
	return (c == '-' || c == '+');
}

static int	check_atoi_min(const char *nptr)
{
	if (nptr[0] == '2' && nptr[1] == '1' && nptr[2] == '4' && nptr[3] == '7' && \
		nptr[4] == '4' && nptr[5] == '8' && nptr[6] == '3' && nptr[7] == '6' && \
		nptr[8] == '4' && nptr[9] == '8')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		result;
	int		sign;

	if (!nptr)
		return (0);
	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (ft_isplus_isminus(nptr[i]))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	if (sign == -1 && check_atoi_min(nptr + i))
		return (-2147483648);
	while (ft_isdigit(nptr[i]))
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
