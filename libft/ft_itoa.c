/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:09:31 by leberton          #+#    #+#             */
/*   Updated: 2025/04/28 06:26:47 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_count(int n)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_set_ismax(char *str, int is_max)
{
	if (is_max)
		str[1] = '2';
}

static char	*itoa_minus(int n)
{
	int		count;
	int		is_max;
	char	*str;

	n = -n;
	is_max = 0;
	if (n == -2147483648)
	{
		is_max = 1;
		n = 147483648;
	}
	count = ft_get_count(n);
	str = (char *)malloc((count + 1 + is_max) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '-';
	ft_set_ismax(str, is_max);
	str[count + is_max + 1] = 0;
	while (count > 0)
	{
		str[count + is_max] = (n % 10) + 48;
		n /= 10;
		count--;
	}
	return (str);
}

static char	*ft_for_0(void)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;

	if (n < 0)
		return (itoa_minus(n));
	else if (n == 0)
		return (ft_for_0());
	count = ft_get_count(n);
	str = (char *)malloc((count + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[count] = 0;
	while (count > 0)
	{
		str[count - 1] = (n % 10) + 48;
		n /= 10;
		count--;
	}
	return (str);
}
