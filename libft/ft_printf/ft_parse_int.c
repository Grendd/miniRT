/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:13:13 by qrigil            #+#    #+#             */
/*   Updated: 2021/01/16 17:13:26 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	print_acc_int(char *str, int save_num, t_flags *flags)
{
	int			char_count;
	int			len_word;

	len_word = (int)ft_strlen(str);
	char_count = 0;
	if (save_num < 0 && flags->acc > -1 && save_num > -2147483648)
		ft_putchar_count('-', 1);
	if (flags->acc >= 0)
		char_count += print_flag_width(flags->acc - len_word, '0');
	char_count += print_str_acc(str, len_word);
	return (char_count);
}

static int	print_width_int(char *str, int save_num, t_flags *flags)
{
	int			len_word;
	int			char_count;
	int			is_zero;

	is_zero = (flags->zero) ? '0' : ' ';
	if (flags->acc >= 0)
		is_zero = ' ';
	char_count = 0;
	len_word = (int)ft_strlen(str);
	if (flags->minus)
		char_count += print_acc_int(str, save_num, flags);
	if (flags->acc > -1 && flags->acc < len_word)
		flags->acc = len_word;
	if (flags->acc >= 0)
	{
		flags->width -= flags->acc;
		char_count += print_flag_width(flags->width, is_zero);
	}
	else
		char_count += print_flag_width(flags->width - len_word, is_zero);
	if (!flags->minus)
		char_count += print_acc_int(str, save_num, flags);
	return (char_count);
}

int			parse_int(int num, t_flags *flags)
{
	int			char_count;
	char		*str;
	int			save_num;

	char_count = 0;
	save_num = num;
	if (!num && flags->acc == 0)
	{
		char_count += print_flag_width(flags->width, ' ');
		return (char_count);
	}
	if (num < 0 && (flags->acc > -1 || flags->zero))
	{
		if (flags->zero && flags->acc <= -1 && num > -2147483648)
			ft_putchar_count('-', 1);
		if (num == -2147483648)
			char_count--;
		num *= -1;
		flags->width--;
		char_count++;
	}
	str = ft_itoa(num);
	char_count += print_width_int(str, save_num, flags);
	free(str);
	return (char_count);
}
