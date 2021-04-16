/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:58:18 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:58:20 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void			parse_sphere(t_scene *rt, char **split_line)
{
	t_elem		*sphere;

	if (!(sphere = ft_calloc(1, sizeof(t_elem))))
		handle_error("Failed to calloc elem", rt);
	if (!check_split(split_line, 4))
		handle_error("Wrong arguments of sphere!", rt);
	sphere->type = SPHERE;
	sphere->coords = parse_vec(split_line[1], rt, 0);
	sphere->diameter = ft_atof(split_line[2]);
	sphere->rgb = parse_rgb(split_line[3], rt);
	if (!rt->objs_list)
		rt->objs_list = ft_lstnew(sphere);
	else
		ft_lstadd_back(&rt->objs_list, ft_lstnew(sphere));
}

void			sphere(t_elem *sphere, t_vec ori, t_vec dir, t_vars *vars)
{
	t_vec		oc;
	float		k1;
	float		k2;
	float		k3;
	float		discr;

	oc = vec_sub(sphere->coords, ori);
	k1 = vec_skal(dir, dir);
	k2 = 2 * vec_skal(oc, dir);
	k3 = vec_skal(oc, oc) - sphere->diameter * sphere->diameter / 4;
	discr = (k2 * k2 - 4 * k1 * k3);
	if (discr < 0)
	{
		vars->t1 = INFINITY;
		vars->t2 = INFINITY;
		return ;
	}
	vars->t1 = (-k2 + sqrtf(discr)) / (2 * k1);
	vars->t2 = (-k2 - sqrtf(discr)) / (2 * k1);
}
