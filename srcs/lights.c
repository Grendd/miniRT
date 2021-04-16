/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:59:40 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:59:43 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

int				shadows(t_scene *rt, t_vars *vars, t_vec ori, t_vec dir)
{
	t_elem		*elem;
	t_list		*tmp;

	vars->shadow_elem = NULL;
	vars->shadow_t = 1;
	tmp = rt->objs_list;
	vars->t1 = INFINITY;
	vars->t2 = INFINITY;
	while (tmp)
	{
		elem = ((t_elem*)tmp->content);
		check_obj(elem, ori, dir, vars);
		if (vars->t1 >= 0.0001 && vars->t1 < vars->shadow_t)
			vars->shadow_t = vars->t1;
		if (vars->t2 >= 0.0001 && vars->t2 < vars->shadow_t)
			vars->shadow_t = vars->t2;
		tmp = tmp->next;
	}
	free(tmp);
	if (vars->shadow_t != 1)
		return (1);
	return (0);
}

void			add_intens(t_color rgb, t_intens *intens, float i)
{
	intens->r += i * rgb.r / 255;
	intens->g += i * rgb.g / 255;
	intens->b += i * rgb.b / 255;
}

void			add_lights(t_vars *vars, t_light light, t_intens *intens)
{
	float		n_dot_l;
	float		i;

	n_dot_l = vec_skal(vars->normal, vec_norm(vec_sub(vars->point,
												light.coords)));
	if (n_dot_l > 0)
	{
		i = (light.ratio * n_dot_l) / (vec_len(vec_norm(
				vec_sub(vars->point, light.coords))) * vec_len(vars->normal));
		add_intens(light.rgb, intens, i);
	}
}

void			add_ref(t_vars *vars, t_light light, t_intens *intes, t_vec dir)
{
	float		r_dot_v;
	t_vec		ref;
	float		i;

	ref = reflect_ray(vec_sub(vars->point, light.coords), vars->normal);
	r_dot_v = vec_skal(ref, vec_rev(dir));
	if (r_dot_v > 0)
	{
		i = light.ratio * powf((r_dot_v /
								(vec_len(ref) * vec_len(vec_rev(dir)))), 500);
		add_intens(light.rgb, intes, i);
	}
}

t_intens		lights(t_vars *vars, t_scene *rt, t_vec dir)
{
	t_list		*tmp;
	float		i;
	t_light		light;
	t_intens	intens;

	i = rt->amb.ratio;
	intens = (t_intens){0, 0, 0};
	add_intens(rt->amb.rgb, &intens, i);
	tmp = rt->lights_list;
	while (tmp)
	{
		light = (*(t_light*)tmp->content);
		tmp = tmp->next;
		if (shadows(rt, vars, vars->point, vec_sub(vars->point, light.coords)))
			continue;
		add_lights(vars, light, &intens);
		add_ref(vars, light, &intens, dir);
	}
	return (intens);
}
