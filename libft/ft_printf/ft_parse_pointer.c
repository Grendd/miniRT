/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:13:54 by qrigil            #+#    #+#             */
/*   Updated: 2021/01/16 17:13:56 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char			*itoa_pointer(unsigned long p)
{
	char			*res;
	int				len;
	unsigned long	p_copy;

	len = 0;
	p_copy = p;
	while (p_copy != 0)
	{
		p_copy /= 16;
		len++;
	}
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res[len] = '\0';
	len--;
	while (p != 0)
	{
		if ((p % 16) < 10)
			res[len] = (p % 16) + 48;
		else
			res[len] = (p % 16) + 87;
		p /= 16;
		len--;
	}
	return (res);
}

static int		print_pointer(char *str, t_flags *flags, unsigned long p)
{
	int char_count;
	int len_word;

	len_word = (p == 0 && flags->acc == 0) ? 0 : (int)ft_strlen(str);
	char_count = 0;
	flags->width -= 2;
	if (flags->minus)
	{
		char_count += print_str_acc("0x", 2);
		char_count += (flags->acc == 0 && p == 0) ? 0
						: print_str_acc(str, len_word);
	}
	if (flags->acc >= 0 && flags->acc > len_word)
		char_count += print_flag_width(flags->width - flags->acc, ' ');
	else
		char_count += print_flag_width(flags->width - len_word, ' ');
	if (!flags->minus)
	{
		char_count += print_str_acc("0x", 2);
		if (flags->acc == 0 && p == 0)
			return (char_count);
		char_count += print_str_acc(str, ft_strlen(str));
	}
	return (char_count);
}

int				parse_pointer(unsigned long p, t_flags *flags)
{
	char			*str;
	int				char_count;

	char_count = 0;
	if (p == 0)
		str = ft_strdup("0");
	else
		str = itoa_pointer(p);
	char_count += print_pointer(str, flags, p);
	free(str);
	return (char_count);
}
