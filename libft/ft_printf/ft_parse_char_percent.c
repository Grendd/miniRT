/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_char_percent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:14:17 by qrigil            #+#    #+#             */
/*   Updated: 2021/01/16 17:14:20 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			parse_char(va_list args, t_flags *flags)
{
	char	c;
	int		char_count;
	int		i;

	i = 0;
	char_count = 0;
	if (flags->star > 0 && !flags->width)
		flags->width = va_arg(args, int);
	c = va_arg(args, int);
	if (flags->width < 0)
	{
		flags->width *= -1;
		flags->minus += 1;
	}
	i = 0;
	if (flags->minus)
		char_count += ft_putchar_count(c, 1);
	char_count += print_flag_width(flags->width - 1, ' ');
	if (!flags->minus)
		char_count += ft_putchar_count(c, 1);
	return (char_count);
}

int			parse_percent(va_list args, t_flags *flags)
{
	int		char_count;
	int		i;
	int		zero;

	i = 0;
	char_count = 0;
	zero = (flags->zero) ? '0' : ' ';
	if (flags->star > 0 && !flags->width)
		flags->width = va_arg(args, int);
	if (flags->minus)
		char_count += ft_putchar_count('%', 1);
	char_count += print_flag_width(flags->width - 1, zero);
	if (!flags->minus)
		char_count += ft_putchar_count('%', 1);
	return (char_count);
}
