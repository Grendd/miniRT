/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:59:20 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:59:23 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_vec		vec_mult(t_vec vec, float num)
{
	vec.x *= num;
	vec.y *= num;
	vec.z *= num;
	return (vec);
}

t_vec		vec_div(t_vec vec, float num)
{
	vec.x /= num;
	vec.y /= num;
	vec.z /= num;
	return (vec);
}

t_vec		vec_norm(t_vec vec)
{
	t_vec	norm;
	float	len;

	len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	norm.x = vec.x / len;
	norm.y = vec.y / len;
	norm.z = vec.z / len;
	return (norm);
}

t_vec		vec_cross(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}
