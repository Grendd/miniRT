/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:48:18 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 14:50:02 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*curr;
	t_list	*prev;

	if (!lst)
		return ;
	if (!(curr = *lst))
		return ;
	while (curr->next)
	{
		prev = curr;
		curr = curr->next;
		if (del)
			del(prev->content);
		free(prev);
	}
	if (del)
		del(curr->content);
	free(curr);
	*lst = NULL;
}
