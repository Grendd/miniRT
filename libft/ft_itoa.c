/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:09:15 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/07 13:09:34 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t	num_len(unsigned int n)
{
	size_t count;

	count = 1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	unsigned int	num;
	char			*res;
	int				minus;
	size_t			res_len;

	minus = 0;
	if (n < 0)
	{
		minus = 1;
		num = -n;
	}
	else
		num = n;
	res_len = num_len(num) + minus;
	if (!(res = (char*)malloc(sizeof(char) * (res_len + 1))))
		return (NULL);
	res[res_len--] = '\0';
	while (num >= 10)
	{
		res[res_len--] = num % 10 + '0';
		num /= 10;
	}
	res[res_len--] = num % 10 + '0';
	minus == 1 ? res[res_len] = '-' : (void)res;
	return (res);
}
