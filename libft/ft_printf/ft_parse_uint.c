/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:14:04 by qrigil            #+#    #+#             */
/*   Updated: 2021/01/16 17:14:07 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

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

static char		*itoa_uint(unsigned int n)
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

static int		print_ui_acc(char *str, t_flags *flags, int len_word)
{
	int			char_count;

	char_count = 0;
	if (flags->acc >= 0)
		char_count += print_flag_width(flags->acc - len_word, '0');
	char_count += print_str_acc(str, len_word);
	return (char_count);
}

static int		print_uint(char *str, t_flags *flags)
{
	int		char_count;
	int		zero;
	int		len_word;

	len_word = (int)ft_strlen(str);
	zero = (flags->zero) ? '0' : ' ';
	char_count = 0;
	if (flags->minus)
		char_count += print_ui_acc(str, flags, len_word);
	if (flags->acc >= 0 && flags->acc < len_word)
		flags->acc = len_word;
	if (flags->acc >= 0)
	{
		flags->width -= flags->acc;
		char_count += print_flag_width(flags->width, ' ');
	}
	else
		char_count += print_flag_width(flags->width - len_word, zero);
	if (!flags->minus)
		char_count += print_ui_acc(str, flags, len_word);
	return (char_count);
}

int				parse_uint(unsigned int num, t_flags *flags)
{
	int			char_count;
	char		*str;

	char_count = 0;
	num = (unsigned int)(num + 4294967295 + 1);
	if (flags->acc == 0 && num == 0)
	{
		char_count += print_flag_width(flags->width, ' ');
		return (char_count);
	}
	str = itoa_uint(num);
	char_count += print_uint(str, flags);
	free(str);
	return (char_count);
}
