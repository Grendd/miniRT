/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:13:44 by qrigil            #+#    #+#             */
/*   Updated: 2021/01/16 17:13:47 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				print_flag_width(int width, int is_zero)
{
	int			char_count;

	char_count = 0;
	while (width > 0)
	{
		width--;
		char_count += ft_putchar_count(is_zero, 1);
	}
	return (char_count);
}

int				print_str_acc(char *str, int acc)
{
	int char_count;

	char_count = 0;
	while (str[char_count] && char_count < acc)
		char_count += ft_putchar_count(str[char_count], 1);
	return (char_count);
}

static int		print_string(char *str, t_flags *flags, int len_word)
{
	int char_count;

	char_count = 0;
	if (flags->acc >= 0)
	{
		char_count += print_flag_width(flags->acc - len_word, ' ');
		char_count += print_str_acc(str, flags->acc);
	}
	else
		char_count += print_str_acc(str, len_word);
	return (char_count);
}

int				parse_string(va_list args, t_flags *flags)
{
	int			len_word;
	int			char_count;
	char		*str;

	char_count = 0;
	str = va_arg(args, char*);
	if (!str)
		str = "(null)";
	len_word = (int)ft_strlen(str);
	if (flags->acc >= 0 && flags->acc > len_word)
		flags->acc = len_word;
	if (flags->minus)
		char_count += print_string(str, flags, len_word);
	if (flags->acc >= 0)
		char_count += print_flag_width(flags->width - flags->acc, ' ');
	else
		char_count += print_flag_width(flags->width - len_word, ' ');
	if (!flags->minus)
		char_count += print_string(str, flags, len_word);
	return (char_count);
}
