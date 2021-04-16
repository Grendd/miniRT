/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:36:17 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 13:39:37 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p_dest;
	char	*p_src;
	size_t	i;

	i = 0;
	p_dest = dest;
	p_src = (char*)src;
	if (dest < src)
	{
		while (i < n)
		{
			p_dest[i] = p_src[i];
			i++;
		}
	}
	else if (dest > src)
	{
		while (i < n)
		{
			i++;
			p_dest[n - i] = p_src[n - i];
		}
	}
	return (dest);
}
