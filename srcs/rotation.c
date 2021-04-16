/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:59:02 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:59:03 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void		rx(t_vec *vec, float x)
{
	t_vec	tmp;

	tmp.x = vec->x;
	tmp.y = vec->y * cos(x) - vec->z * sin(x);
	tmp.z = vec->y * sin(x) + vec->z * cos(x);
	*vec = tmp;
}

void		ry(t_vec *vec, float y)
{
	t_vec	tmp;

	tmp.x = vec->x * cos(y) + vec->z * sin(y);
	tmp.y = vec->y;
	tmp.z = vec->x * -sin(y) + vec->z * cos(y);
	*vec = tmp;
}

void		rz(t_vec *vec, float z)
{
	t_vec	tmp;

	tmp.x = vec->x * cos(z) - vec->y * sin(z);
	tmp.y = vec->x * sin(z) + vec->y * cos(z);
	tmp.z = vec->z;
	*vec = tmp;
}

void		rot(t_vec *vec, t_vec *angle)
{
	rx(vec, angle->x);
	ry(vec, angle->y);
	rz(vec, angle->z);
}

void		anti_rot(t_vec *vec, t_vec *angle)
{
	rz(vec, -angle->z);
	ry(vec, -angle->y);
	rx(vec, -angle->x);
}
