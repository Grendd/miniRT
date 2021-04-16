/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:41:35 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 14:42:47 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *str, size_t n)
{
	char	*ptr;
	size_t	i;

	if (!n)
		return ;
	ptr = str;
	i = 0;
	while (i < n)
		ptr[i++] = 0;
}
