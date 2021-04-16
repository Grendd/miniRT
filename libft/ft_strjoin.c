/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:36:24 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 14:40:56 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(result = (char*)malloc((len1 + len2 + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (j < len2)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
