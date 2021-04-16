/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:04:13 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 15:05:19 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		nlen;
	const char	*str;

	nlen = ft_strlen(needle);
	str = haystack;
	if (nlen == 0)
		return ((char*)haystack);
	if (ft_strlen(haystack) == 0)
		return (0);
	while (((haystack = ft_strchr(haystack, needle[0])) - str) + nlen <= len)
	{
		if (!ft_strncmp(haystack, needle, nlen))
			return ((char *)haystack);
		++haystack;
	}
	return (0);
}
