/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:37:15 by leberton          #+#    #+#             */
/*   Updated: 2025/04/28 06:29:07 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	size_t	size;

	size = (ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char);
	new = ft_calloc(size, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcat(new, s1, size);
	ft_strlcat(new + ft_strlen(s1), s2, size);
	return (new);
}
