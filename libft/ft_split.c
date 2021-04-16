/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:59:41 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 14:12:39 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t		count_words(char const *str, char c)
{
	size_t		count;
	char		find;

	count = 0;
	find = 1;
	while (*str)
	{
		if (*str == c && !find)
			find = 1;
		else if (*str != c && find)
		{
			count++;
			find = 0;
		}
		str++;
	}
	return (count);
}

static size_t		len_word(char const *str, char c)
{
	size_t		i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static void			*free_array(void **array, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
		free(array[i++]);
	free(array);
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	char		**result;
	size_t		arr_len;
	size_t		i;
	size_t		j;
	size_t		len;

	if (!s)
		return (NULL);
	arr_len = count_words(s, c);
	if (!(result = (char**)malloc(sizeof(char*) * (arr_len + 1))))
		return (NULL);
	i = 0;
	while (i < arr_len && *s && !(j = 0))
	{
		while (*s == c)
			s++;
		len = len_word(s, c);
		if (!(result[i] = (char*)malloc((len + 1) * sizeof(char))))
			return (free_array((void**)result, i));
		while (j < len)
			result[i][j++] = *(s++);
		result[i++][j] = '\0';
	}
	result[arr_len] = NULL;
	return (result);
}
