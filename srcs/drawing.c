/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:58:36 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:58:38 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void			square(t_elem *square, t_vec ori, t_vec dir, t_vars *vars)
{
	t_vec		d;
	float		x;
	float		y;
	float		t;
	float		side;

	x = vec_skal(vec_sub(square->coords, ori), square->norm);
	y = vec_skal(square->norm, dir);
	if (y == 0 || (x < 0 && y < 0) || (x > 0 && y > 0))
		return ;
	t = -x / y;
	d = vec_sub(square->coords, vec_add(vec_mult(dir, t), ori));
	side = square->side_size / 2;
	if (fabsf(d.x) > side || fabsf(d.y) > side || fabsf(d.z) > side)
		return ;
	vars->t1 = t;
}

void			plane(t_elem *plane, t_vec ori, t_vec dir, t_vars *vars)
{
	float		x;
	float		y;
	float		t;

	x = vec_skal(vec_sub(plane->coords, ori), vec_norm(plane->norm));
	y = vec_skal(vec_norm(plane->norm), dir);
	if (y == 0 || (x < 0 && y < 0) || (x > 0 && y > 0))
		return ;
	t = -x / y;
	if (t < 0 || vars->t1 < t)
		return ;
	vars->t1 = t;
}

void			triangle(t_elem *tri, t_vec ori, t_vec dir, t_vars *vars)
{
	t_vec		v1;
	t_vec		v2;
	t_vec		tvec;
	t_vec		pvec;
	float		det;

	v1 = vec_sub(tri->t1, tri->t2);
	v2 = vec_sub(tri->t1, tri->t3);
	pvec = vec_cross(dir, v2);
	det = vec_skal(v1, pvec);
	if (fabsf(det) < 0.00001)
		return ;
	vars->c = 1 / det;
	tvec = vec_sub(tri->t1, ori);
	vars->a = vec_skal(tvec, pvec) * vars->c;
	if (vars->a < 0 || vars->a > 1)
		return ;
	tvec = vec_cross(tvec, v1);
	vars->b = vec_skal(dir, tvec) * vars->c;
	if (vars->b < 0 || vars->a + vars->b > 1)
		return ;
	vars->t1 = vec_skal(v2, tvec) * vars->c;
}
