/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:06:45 by leberton          #+#    #+#             */
/*   Updated: 2025/04/28 06:21:39 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	final_len;
	char	*final;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	final_len = s_len - start;
	if (final_len > len)
		final_len = len;
	final = (char *)malloc((final_len + 1) * sizeof(char));
	if (!final)
		return (NULL);
	i = 0;
	while (i < final_len)
	{
		final[i] = s[start + i];
		i++;
	}
	final[i] = 0;
	return (final);
}
