/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:24:45 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 13:26:39 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	res;
	size_t	dlen;

	dlen = ft_strlen(dst);
	if (dstsize <= dlen)
		return (dstsize + ft_strlen(src));
	else
	{
		res = dlen + ft_strlen(src);
		dst += dlen;
		while (*src && dstsize-- - dlen > 1)
			*dst++ = *src++;
		*dst = 0;
		return (res);
	}
}
