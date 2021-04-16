/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:13:34 by qrigil            #+#    #+#             */
/*   Updated: 2021/01/16 17:13:37 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*hex_convert(unsigned long arg, int len, int is_upper)
{
	char *res;

	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res[len] = '\0';
	if (arg == 0)
	{
		res[0] = '0';
		return (res);
	}
	while (arg != 0)
	{
		if ((arg % 16) < 10)
			res[len - 1] = (arg % 16) + 48;
		else
			res[len - 1] = (arg % 16) + 55;
		if (!is_upper)
			res[len - 1] = ft_tolower(res[len - 1]);
		arg /= 16;
		len--;
	}
	return (res);
}

static int		print_acc_str(char *str, t_flags *flags, int len_word)
{
	int		char_count;

	char_count = 0;
	if (flags->acc >= 0)
		char_count += print_flag_width(flags->acc - len_word, '0');
	char_count += print_str_acc(str, len_word);
	return (char_count);
}

static int		print_hex(char *str, t_flags *flags)
{
	int char_count;
	int len_word;
	int zero_or_space;

	zero_or_space = (flags->zero) ? '0' : ' ';
	char_count = 0;
	len_word = (int)ft_strlen(str);
	if (flags->minus)
		char_count += print_acc_str(str, flags, len_word);
	if (flags->acc >= 0 && flags->acc < len_word)
		flags->acc = len_word;
	if (flags->acc >= 0)
	{
		flags->width -= flags->acc;
		char_count += print_flag_width(flags->width, ' ');
	}
	else
		char_count += print_flag_width(flags->width - len_word, zero_or_space);
	if (!flags->minus)
		char_count += print_acc_str(str, flags, len_word);
	return (char_count);
}

int				parse_hex(va_list args, t_flags *flags, int is_upper)
{
	int				len;
	unsigned int	number;
	unsigned int	number_save;
	char			*res;
	int				char_count;

	char_count = 0;
	len = 0;
	number = va_arg(args, unsigned int);
	number = (unsigned int)(number + 4294967295 + 1);
	number_save = number;
	if (!number && flags->acc == 0)
	{
		char_count += print_flag_width(flags->width, ' ');
		return (char_count);
	}
	while (number != 0 && ++len)
		number /= 16;
	if (number_save == 0)
		len = 1;
	res = hex_convert((unsigned long)number_save, len, is_upper);
	char_count += print_hex(res, flags);
	free(res);
	return (char_count);
}
