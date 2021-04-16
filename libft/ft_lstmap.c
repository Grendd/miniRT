/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:20:11 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 14:21:47 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*curr;

	if (!lst || !f)
		return (NULL);
	if (!(curr = ft_lstnew(f(lst->content))))
		return (NULL);
	head = curr;
	while (lst->next)
	{
		lst = lst->next;
		if (!(curr->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		curr = curr->next;
	}
	return (head);
}
