/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:12:52 by qrigil            #+#    #+#             */
/*   Updated: 2021/01/16 17:12:55 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				is_type(int c)
{
	return ((c == 'c') || (c == 's') || (c == 'p') || (c == 'd') || (c == 'i')
			|| (c == 'u') || (c == 'x') || (c == 'X') || (c == '%'));
}

int				is_flag(int c)
{
	return ((c == '-') || (c == ' ') || (c == '0') || (c == '.') || (c == '*'));
}

void			neg_width(t_flags *flags)
{
	if (flags->width < 0)
	{
		flags->width *= -1;
		flags->minus = 1;
		flags->zero = 0;
	}
}

t_flags			ft_init_flags(void)
{
	t_flags		flags;

	flags.minus = 0;
	flags.width = 0;
	flags.zero = 0;
	flags.star = 0;
	flags.acc = -1;
	return (flags);
}

void			ft_digits_parse(const char *save, int i, t_flags *flags)
{
	if (flags->acc == -1)
		flags->width = flags->width * 10 + (save[i] - '0');
	else
		flags->acc = flags->acc * 10 + (save[i] - '0');
}
