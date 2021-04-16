/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:54:42 by qrigil            #+#    #+#             */
/*   Updated: 2021/01/16 16:55:47 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	parse_type(int type_char, va_list args, t_flags *flags)
{
	int		char_count;

	char_count = 0;
	if (type_char == 'c')
		char_count += parse_char(args, flags);
	else if (type_char == 's')
		char_count += parse_string(args, flags);
	else if (type_char == 'p')
		char_count += parse_pointer(va_arg(args, unsigned long), flags);
	else if (type_char == 'i' || type_char == 'd')
		char_count += parse_int(va_arg(args, int), flags);
	else if (type_char == 'u')
		char_count += parse_uint(va_arg(args, unsigned int), flags);
	else if (type_char == 'x')
		char_count += parse_hex(args, flags, 0);
	else if (type_char == 'X')
		char_count += parse_hex(args, flags, 1);
	else if (type_char == '%')
		char_count += parse_percent(args, flags);
	return (char_count);
}

static int	parse_flags(const char *save, int i, t_flags *flags, va_list args)
{
	while (save[i])
	{
		if ((!ft_isdigit(save[i]) && !is_flag(save[i])) || is_type(save[i]))
			break ;
		if (save[i] == '.')
			flags->acc = 0;
		else if (save[i] == '0' && !flags->width
				&& flags->acc == -1 && !flags->minus)
			flags->zero = 1;
		else if (ft_isdigit(save[i]))
			ft_digits_parse(save, i, flags);
		else if (save[i] == '*')
		{
			if (flags->acc == -1)
				flags->width = va_arg(args, int);
			else if (flags->acc == 0)
				flags->acc = va_arg(args, int);
		}
		else if (save[i] == '-')
			flags->minus = 1;
		i++;
	}
	return (i);
}

static int	parser(const char *save, va_list args)
{
	int			i;
	int			char_count;
	t_flags		flags;

	i = 0;
	char_count = 0;
	while (1)
	{
		flags = ft_init_flags();
		if (!save[i])
			break ;
		else if (save[i] == '%' && save[i + 1])
		{
			i = parse_flags(save, ++i, &flags, args);
			neg_width(&flags);
			if (is_type(save[i]))
				char_count += parse_type(save[i], args, &flags);
			else if (save[i])
				char_count += ft_putchar_count(save[i], 1);
		}
		else if (save[i] != '%')
			char_count += ft_putchar_count(save[i], 1);
		i++;
	}
	return (char_count);
}

int			ft_printf(const char *str, ...)
{
	va_list		args;
	const char	*save;
	int			char_count;

	if (!(save = ft_strdup(str)))
		return (-1);
	char_count = 0;
	va_start(args, str);
	char_count += parser(save, args);
	va_end(args);
	free((char *)save);
	return (char_count);
}
