/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:58:26 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:58:29 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void			check_type(char **split, t_scene *rt)
{
	if (ft_strcmp(split[0], "R") == 0)
		parse_resol(rt, split);
	else if (ft_strcmp(split[0], "A") == 0)
		parse_amb(rt, split);
	else if (ft_strcmp(split[0], "c") == 0)
		parse_cams(rt, split);
	else if (ft_strcmp(split[0], "l") == 0)
		parse_lights(rt, split);
	else if (ft_strcmp(split[0], "pl") == 0)
		parse_plane(rt, split);
	else if (ft_strcmp(split[0], "sp") == 0)
		parse_sphere(rt, split);
	else if (ft_strcmp(split[0], "sq") == 0)
		parse_square(rt, split);
	else if (ft_strcmp(split[0], "cy") == 0)
		parse_cylinder(rt, split);
	else if (ft_strcmp(split[0], "tr") == 0)
		parse_triangle(rt, split);
	else
		handle_error("Wrong identifier", rt);
}

static void		treat_line(t_scene *rt, char **line)
{
	char		**split_line;

	split_line = ft_split(*line, ' ');
	free(*line);
	check_type(split_line, rt);
	free_split(split_line);
}

int				parse_rt(t_scene *rt, char *filename)
{
	char		*line;
	int			fd;

	if (!(fd = open(filename, O_RDONLY)))
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		treat_line(rt, &line);
	}
	if (ft_strcmp(line, "") != 0)
		treat_line(rt, &line);
	line = 0;
	if (!rt->cams_list)
		handle_error("Not enough cameras", rt);
	close(fd);
	return (1);
}
