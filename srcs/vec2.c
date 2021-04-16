/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:05:45 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 15:05:47 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_vec		vec_add(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = b.x + a.x;
	vec.y = b.y + a.y;
	vec.z = b.z + a.z;
	return (vec);
}

t_vec		vec_sub(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = b.x - a.x;
	vec.y = b.y - a.y;
	vec.z = b.z - a.z;
	return (vec);
}

t_vec		vec_rev(t_vec a)
{
	a.x *= -1;
	a.y *= -1;
	a.z *= -1;
	return (a);
}

float		vec_skal(t_vec a, t_vec b)
{
	return (b.x * a.x + b.y * a.y + b.z * a.z);
}

float		vec_len(t_vec a)
{
	return (sqrtf(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}
