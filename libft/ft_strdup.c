/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:19:05 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 13:21:49 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *str1)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!(str = (char*)malloc((ft_strlen(str1) + 1) * sizeof(char))))
		return (NULL);
	while (str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
