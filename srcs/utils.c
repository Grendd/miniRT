/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:59:53 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:59:54 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void			print_pixel(t_image *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int				check_split(char **split, int len)
{
	int			i;

	i = 0;
	while (split[i])
		i++;
	return (i == len);
}

static float	atof_oper(char c, float res, float *mult, int toggle)
{
	if (!toggle)
		res = res * 10 + (float)(c - '0');
	else
	{
		res = (res + (float)(c - '0') * *mult);
		*mult *= (float)0.1;
	}
	return (res);
}

float			ft_atof(char *split)
{
	float		res;
	int			toggle;
	float		multiply;
	float		min;

	if (!ft_strchr(split, '.'))
		return (float)ft_atoi(split);
	toggle = 0;
	multiply = 0.1;
	res = 0;
	min = 1;
	while (*split)
	{
		min = (*split == '-') ? min * (-1) : min;
		toggle = (*split == '.') ? 1 : toggle;
		if (*split >= '0' && *split <= '9')
			res = atof_oper(*split, res, &multiply, toggle);
		split++;
	}
	res *= min;
	return (res);
}

void			free_split(char **line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
	line = NULL;
}
