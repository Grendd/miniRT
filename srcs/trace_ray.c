/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:59:09 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:59:12 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void			check_obj(t_elem *elem, t_vec ori, t_vec dir, t_vars *vars)
{
	if (elem->type == SPHERE)
		sphere(elem, ori, dir, vars);
	if (elem->type == SQUARE)
		square(elem, ori, dir, vars);
	if (elem->type == PLANE)
		plane(elem, ori, dir, vars);
	if (elem->type == TRIANGLE)
		triangle(elem, ori, dir, vars);
	if (elem->type == CYLINDER)
		cylinder(elem, ori, dir, vars);
}

void			interseption(t_scene *rt, t_vars *vars, t_vec ori, t_vec dir)
{
	t_elem		*elem;
	t_list		*tmp;

	vars->cl_el = NULL;
	vars->cl_t = INFINITY;
	vars->t1 = INFINITY;
	vars->t2 = INFINITY;
	tmp = rt->objs_list;
	while (tmp)
	{
		elem = (t_elem*)tmp->content;
		check_obj(elem, ori, dir, vars);
		if (vars->t1 > 1 && vars->t1 < vars->cl_t)
		{
			vars->cl_t = vars->t1;
			vars->cl_el = elem;
		}
		if ((elem->type == SPHERE || elem->type == CYLINDER) &&
		vars->t2 > 1 && vars->t2 < vars->cl_t)
		{
			vars->cl_t = vars->t2;
			vars->cl_el = elem;
		}
		tmp = tmp->next;
	}
}

float			vector_angle_cos(t_vec vec1, t_vec vec2)
{
	float		cos;

	cos = vec_skal(vec1, vec2);
	cos /= vec_len(vec1);
	cos /= vec_len(vec2);
	return (cos);
}

t_vec			get_norm_vec(t_vars *vars)
{
	t_vec		norm;

	norm = (t_vec){0, 0, 0};
	if (vars->cl_el->type == PLANE || vars->cl_el->type == SQUARE ||
									vars->cl_el->type == TRIANGLE)
		norm = vec_norm(vars->cl_el->norm);
	else if (vars->cl_el->type == SPHERE)
	{
		norm = vec_sub(vars->cl_el->coords, vars->point);
		norm = vec_div(norm, vec_len(norm));
	}
	else if (vars->cl_el->type == CYLINDER)
		norm = get_cylinder_normal(vars->cl_el, vars->point);
	if (vector_angle_cos(vars->dir, norm) > 0)
		norm = vec_mult(norm, -1);
	return (norm);
}

t_color			trace_ray(t_scene *rt, t_vec dir, t_vec ori, int depth)
{
	t_color		loc_color;
	t_vars		vars;
	t_vec		ref;
	t_color		ref_color;

	interseption(rt, &vars, ori, dir);
	if (!vars.cl_el)
		return (convert_to_rgb(BACKGROUND_COLOR));
	vars.dir = dir;
	vars.point = vec_add(ori, vec_mult(dir, vars.cl_t));
	vars.normal = get_norm_vec(&vars);
	loc_color = col_int(vars.cl_el->rgb, lights(&vars, rt, dir));
	if (depth <= 0 || (vars.cl_el->type != SPHERE &&
							vars.cl_el->type != CYLINDER))
		return (loc_color);
	ref = reflect_ray(vec_rev(dir), vars.normal);
	ref_color = trace_ray(rt, ref, vars.point, depth - 1);
	return (col_add(loc_color, col_intens(ref_color, REFLECT), 1));
}
