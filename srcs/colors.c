/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:58:10 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:58:12 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_color			convert_to_rgb(int color)
{
	t_color		rgb;

	rgb.b = (color & (0xFF << 0)) >> 0;
	rgb.g = (color & (0xFF << 8)) >> 8;
	rgb.r = (color & (0xFF << 16)) >> 16;
	return (rgb);
}

int				convert_to_int(t_color rgb)
{
	rgb.r = (rgb.r) > 255 ? 255 : rgb.r;
	rgb.g = (rgb.g) > 255 ? 255 : rgb.g;
	rgb.b = (rgb.b) > 255 ? 255 : rgb.b;
	return ((0 << 24) | (rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

t_color			col_intens(t_color rgb, float i)
{
	if (i > 1)
		return (rgb);
	rgb.r = (int)((float)rgb.r * i);
	rgb.g = (int)((float)rgb.g * i);
	rgb.b = (int)((float)rgb.b * i);
	return (rgb);
}

t_color			col_int(t_color rgb, t_intens i)
{
	if (i.r > 1 || i.g > 1 || i.b > 1)
		return (rgb);
	rgb.r = (int)((float)rgb.r * i.r);
	rgb.g = (int)((float)rgb.g * i.g);
	rgb.b = (int)((float)rgb.b * i.b);
	rgb.r = (rgb.r) > 255 ? 255 : rgb.r;
	rgb.g = (rgb.g) > 255 ? 255 : rgb.g;
	rgb.b = (rgb.b) > 255 ? 255 : rgb.b;
	return (rgb);
}

t_color			col_add(t_color col1, t_color col2, float i)
{
	t_color		color;

	color.r = col1.r + col2.r;
	color.r > 255 && i ? color.r = 255 : 0;
	color.g = col1.g + col2.g;
	color.g > 255 && i ? color.g = 255 : 0;
	color.b = col1.b + col2.b;
	color.b > 255 && i ? color.b = 255 : 0;
	return (color);
}
