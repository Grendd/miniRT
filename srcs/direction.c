/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 21:43:54 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/29 21:44:06 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void		compute_pixel(float *x, float *y, t_resol *res, t_cam *cam)
{
	float	aspect;
	float	px;
	float	py;
	float	width;
	float	height;

	width = (float)res->x;
	height = (float)res->y;
	if (width > height)
		aspect = width / height;
	else
		aspect = height / width;
	px = (2 * (*x + 0.5) / width - 1) * tan(cam->fov * M_PI / 360.0);
	py = (1 - 2 * (*y + 0.5) / height) * tan(cam->fov * M_PI / 360.0);
	if (width > height)
		px *= aspect;
	else
		py *= aspect;
	*x = px;
	*y = py;
}

t_vec		calculate_direction(t_cam *cam, t_scene *rt, float x, float y)
{
	float	**matrix;
	t_vec	temp;
	t_vec	dir;

	compute_pixel(&x, &y, &rt->res, cam);
	temp = (t_vec){x, y, -1};
	matrix = matrix_create(cam);
	dir = matrix_mult(matrix, temp);
	matrix_free(matrix);
	return (dir);
}
