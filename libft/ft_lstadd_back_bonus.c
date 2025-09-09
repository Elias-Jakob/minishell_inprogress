/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:19:14 by leberton          #+#    #+#             */
/*   Updated: 2025/04/27 21:21:45 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	t_list *swap;

	if (!lst || !new_lst)
		return;
	if (*lst == NULL)
	{
		*lst = new_lst;
		return;
	}
	swap = *lst;
	while (swap->next)
		swap = swap->next;
	swap->next = new_lst;
}
