/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:15:17 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 15:15:18 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void			parse_resol(t_scene *rt, char **split_line)
{
	if (!check_split(split_line, 3))
		handle_error("Wrong arguments of resolution!", rt);
	rt->res.x = ft_atoi(split_line[1]);
	rt->res.y = ft_atoi(split_line[2]);
}

void			parse_amb(t_scene *rt, char **split_line)
{
	if (!check_split(split_line, 3))
		handle_error("Wrong arguments of ambient!", rt);
	rt->amb.ratio = ft_atof(split_line[1]);
	if (rt->amb.ratio < 0 || rt->amb.ratio > 1)
		handle_error("Wrong ratio of ambient!", rt);
	rt->amb.rgb = parse_rgb(split_line[2], rt);
}

void			parse_cams(t_scene *rt, char **split_line)
{
	t_cam		*camera;

	if (!(camera = ft_calloc(1, sizeof(t_cam))))
		handle_error("Failed to calloc elem", rt);
	if (!check_split(split_line, 4))
		handle_error("Wrong arguments of camera!", rt);
	camera->coords = parse_vec(split_line[1], rt, 0);
	camera->orient = parse_vec(split_line[2], rt, 1);
	camera->fov = ft_atoi(split_line[3]);
	if (!rt->cams_list)
		rt->cams_list = ft_lstnew(camera);
	else
		ft_lstadd_back(&rt->cams_list, ft_lstnew(camera));
}

void			parse_lights(t_scene *rt, char **split_line)
{
	t_light		*light;

	if (!(light = ft_calloc(1, sizeof(t_light))))
		handle_error("Failed to calloc elem", rt);
	if (!check_split(split_line, 4))
		handle_error("Wrong arguments of light!", rt);
	light->coords = parse_vec(split_line[1], rt, 0);
	light->ratio = ft_atof(split_line[2]);
	if (light->ratio < 0 || light->ratio > 1)
		handle_error("Wrong ratio of light!", rt);
	light->rgb = parse_rgb(split_line[3], rt);
	if (!rt->lights_list)
		rt->lights_list = ft_lstnew(light);
	else
		ft_lstadd_back(&rt->lights_list, ft_lstnew(light));
}
