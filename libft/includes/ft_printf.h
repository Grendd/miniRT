/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:50:22 by qrigil            #+#    #+#             */
/*   Updated: 2021/01/16 16:53:44 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef	struct		s_flags
{
	int			minus;
	int			width;
	int			acc;
	int			zero;
	int			star;
}					t_flags;

t_flags				ft_init_flags(void);
int					ft_printf(const char *str, ...);
int					parse_hex(va_list args, t_flags *flags, int is_upper);
int					parse_string(va_list args, t_flags *flags);
int					parse_int(int num, t_flags *flags);
int					parse_char(va_list args, t_flags *flags);
int					parse_percent(va_list args, t_flags *flags);
int					parse_pointer(unsigned long p, t_flags *flags);
int					parse_uint(unsigned int num, t_flags *flags);
int					print_flag_width(int width, int is_zero);
int					print_str_acc(char *str, int acc);
int					ft_putchar_count(char c, int fd);
int					ft_putnbr_count(int n, int fd);
int					is_type(int c);
int					is_flag(int c);
void				neg_width(t_flags *flags);
void				ft_digits_parse(const char *save, int i, t_flags *flags);

#endif
