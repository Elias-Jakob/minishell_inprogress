/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:03:33 by leberton          #+#    #+#             */
/*   Updated: 2025/04/27 22:07:45 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_to_trim(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*copy_new_str(const char *s1, size_t start, size_t len)
{
	size_t		i;
	char		*new;

	if (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s1[start + i];
		i++;
	}
	return (new);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t		i;
	size_t		j;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	i = 0;
	while (is_to_trim(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (is_to_trim(set, s1[j]))
		j--;
	return (copy_new_str(s1, i, j - i + 1));
}
