/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:06:10 by leberton          #+#    #+#             */
/*   Updated: 2025/04/27 21:39:07 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s;

	if (!s)
		return (NULL);
	i = 0;
	ptr_s = (unsigned char *)s;
	while (i < n)
	{
		if (*(ptr_s + i) == (unsigned char)c)
			return (ptr_s + i);
		i++;
	}
	return (NULL);
}
