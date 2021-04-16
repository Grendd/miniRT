/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:57:39 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:57:49 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void			parse_cylinder(t_scene *rt, char **split_line)
{
	t_elem		*cylinder;

	if (!(cylinder = ft_calloc(1, sizeof(t_elem))))
		handle_error("Failed to calloc elem", rt);
	if (!check_split(split_line, 6))
		handle_error("Wrong arguments of plane!", rt);
	cylinder->type = CYLINDER;
	cylinder->coords = parse_vec(split_line[1], rt, 0);
	cylinder->norm = vec_norm(parse_vec(split_line[2], rt, 1));
	cylinder->diameter = ft_atof(split_line[3]);
	cylinder->height = ft_atof(split_line[4]);
	cylinder->rgb = parse_rgb(split_line[5], rt);
	cylinder->t1 = vec_add(cylinder->coords, vec_mult(vec_norm(cylinder->norm),
													cylinder->height / 2));
	cylinder->t2 = vec_add(cylinder->coords, vec_mult(vec_norm(cylinder->norm),
													cylinder->height / -2));
	if (!rt->objs_list)
		rt->objs_list = ft_lstnew(cylinder);
	else
		ft_lstadd_back(&rt->objs_list, ft_lstnew(cylinder));
}

t_vec			get_cylinder_normal(t_elem *cyl, t_vec p)
{
	t_elem		plan;
	t_vars		vars;

	plan.norm = cyl->norm;
	plan.coords = cyl->coords;
	vars.t1 = INFINITY;
	plane(&plan, p, cyl->norm, &vars);
	if (vars.t1 != INFINITY)
	{
		return (vec_norm(vec_sub(vec_add(cyl->coords,
						vec_mult(cyl->norm, vars.t1 * -1)), p)));
	}
	plane(&plan, p, vec_mult(cyl->norm, -1), &vars);
	return (vec_norm(vec_sub(vec_add(cyl->coords,
								vec_mult(cyl->norm, vars.t1)), p)));
}

void			check_cyl_height(t_elem *cylinder, t_vec inter, t_vars vars2,
						t_vars *vars)
{
	t_elem		plan;
	float		t;

	t = cylinder->side_size;
	plan.norm = cylinder->norm;
	plan.coords = cylinder->coords;
	vars2.t1 = INFINITY;
	plane(&plan, inter, cylinder->norm, &vars2);
	(vars2.t1 > 0 && vars2.t1 <= cylinder->height / 2) ? vars->t1 = t : 0;
	plane(&plan, inter, vec_mult(cylinder->norm, -1), &vars2);
	(vars2.t1 > 0 && vars2.t1 <= cylinder->height / 2) ? vars->t1 = t : 0;
}

void			inter(t_elem *cylinder, t_vec ori, t_vars vars2, t_vars *vars)
{
	t_elem		plan;
	t_vec		inter;
	float		t;

	t = INFINITY;
	plan.norm = cylinder->norm;
	plan.coords = cylinder->coords;
	if (vars2.t1 >= 0 && vars->t1 > vars2.t1)
	{
		t = vars2.t1;
		inter = vec_add(ori, vec_mult(vars2.dir, t));
		cylinder->side_size = t;
		check_cyl_height(cylinder, inter, vars2, vars);
	}
	if (vars2.t2 >= 0 && vars->t1 > vars2.t2)
	{
		t = vars2.t2;
		inter = vec_add(ori, vec_mult(vars2.dir, t));
		cylinder->side_size = t;
		check_cyl_height(cylinder, inter, vars2, vars);
	}
}

void			cylinder(t_elem *cyl, t_vec ori, t_vec dir, t_vars *vars)
{
	t_vec		cross;
	t_vec		cross2;
	t_vec		sub;
	float		det;
	t_vars		vars2;

	cross = vec_cross(dir, cyl->norm);
	sub = vec_sub(cyl->coords, ori);
	cross2 = vec_cross(sub, cyl->norm);
	vars->a = vec_skal(cross, cross);
	vars->b = 2 * vec_skal(cross, cross2);
	vars->c = vec_skal(cross2, cross2) - (powf(cyl->diameter / 2, 2) *
									vec_skal(cyl->norm, cyl->norm));
	det = powf(vars->b, 2) - (4 * vars->a * vars->c);
	if (det < 0)
		return ;
	vars->a = 2 * vars->a;
	det = sqrtf(det);
	vars2.t1 = (-vars->b - det) / vars->a;
	vars2.t2 = (-vars->b + det) / vars->a;
	vars2.dir = dir;
	inter(cyl, ori, vars2, vars);
}
