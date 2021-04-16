/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:05:56 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 15:06:00 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_color			parse_rgb(char *split_line, t_scene *rt)
{
	t_color		rgb;
	char		**split;

	split = ft_split(split_line, ',');
	if (!check_split(split, 3))
		handle_error("Wrong arguments of rgb!", rt);
	rgb.r = ft_atoi(split[0]);
	rgb.g = ft_atoi(split[1]);
	rgb.b = ft_atoi(split[2]);
	if (rgb.r < 0 || rgb.r > 255 || rgb.g < 0 || rgb.g > 255 || rgb.b < 0 ||
																rgb.b > 255)
		handle_error("Wrong value of color!", rt);
	free_split(split);
	return (rgb);
}

t_vec			parse_vec(char *split_line, t_scene *rt, int i)
{
	t_vec		vec;
	char		**split;

	split = ft_split(split_line, ',');
	if (!check_split(split, 3))
		handle_error("Wrong arguments of vector!", rt);
	vec.x = ft_atof(split[0]);
	vec.y = ft_atof(split[1]);
	vec.z = ft_atof(split[2]);
	if (i)
		if (vec.x > 1 || vec.x < -1 || vec.y > 1 || vec.y < -1 || vec.z > 1 ||
			vec.z < -1)
			handle_error("Wrong value of vec!", rt);
	free_split(split);
	return (vec);
}

void			parse_plane(t_scene *rt, char **split_line)
{
	t_elem		*plane;

	if (!check_split(split_line, 4))
		handle_error("Wrong arguments of plane!", rt);
	if (!(plane = ft_calloc(1, sizeof(t_elem))))
		handle_error("Failed to calloc elem", rt);
	plane->type = PLANE;
	plane->coords = parse_vec(split_line[1], rt, 0);
	plane->norm = parse_vec(split_line[2], rt, 1);
	plane->rgb = parse_rgb(split_line[3], rt);
	if (!rt->objs_list)
		rt->objs_list = ft_lstnew(plane);
	else
		ft_lstadd_back(&rt->objs_list, ft_lstnew(plane));
}

void			parse_square(t_scene *rt, char **split_line)
{
	t_elem		*square;

	if (!check_split(split_line, 5))
		handle_error("Wrong arguments of square!", rt);
	if (!(square = ft_calloc(1, sizeof(t_elem))))
		handle_error("Failed to calloc elem", rt);
	square->type = SQUARE;
	square->coords = parse_vec(split_line[1], rt, 0);
	square->norm = parse_vec(split_line[2], rt, 1);
	square->side_size = ft_atof(split_line[3]);
	square->rgb = parse_rgb(split_line[4], rt);
	if (!rt->objs_list)
		rt->objs_list = ft_lstnew(square);
	else
		ft_lstadd_back(&rt->objs_list, ft_lstnew(square));
}

void			parse_triangle(t_scene *rt, char **split_line)
{
	t_elem		*tri;

	if (!check_split(split_line, 5))
		handle_error("Wrong arguments of triangle!", rt);
	if (!(tri = ft_calloc(1, sizeof(t_elem))))
		handle_error("Failed to calloc elem", rt);
	tri->type = TRIANGLE;
	tri->t1 = parse_vec(split_line[1], rt, 0);
	tri->t2 = parse_vec(split_line[2], rt, 0);
	tri->t3 = parse_vec(split_line[3], rt, 0);
	tri->rgb = parse_rgb(split_line[4], rt);
	tri->norm = vec_norm(vec_cross(vec_sub(tri->t2, tri->t1),
								vec_sub(tri->t3, tri->t2)));
	if (!rt->objs_list)
		rt->objs_list = ft_lstnew(tri);
	else
		ft_lstadd_back(&rt->objs_list, ft_lstnew(tri));
}
