/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:58:52 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:58:54 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_vec		reflect_ray(t_vec dir, t_vec norm)
{
	t_vec	ref;

	ref = vec_sub(dir, vec_mult(vec_mult(norm, 2), vec_skal(norm, dir)));
	return (ref);
}

void		render_image(t_scene *rt)
{
	int		x;
	int		y;
	int		color;
	t_cam	*cam;
	t_vec	dir;

	y = 0;
	cam = ((t_cam*)rt->cams_list->content);
	calculate_axis(cam);
	while (y < rt->res.y)
	{
		x = 0;
		while (x < rt->res.x)
		{
			dir = calculate_direction(cam, rt, (float)x, (float)y);
			color = convert_to_int(trace_ray(rt, dir, cam->coords, 3));
			print_pixel(&rt->img, x, y, color);
			x++;
		}
		y++;
	}
}

void		init_mlx(t_scene *rt, int argc)
{
	int		x_scr;
	int		y_scr;

	if (!(rt->mlx = mlx_init()))
		handle_error("Failed to init miniLibX", rt);
	if (argc == 2)
	{
		mlx_get_screen_size(rt->mlx, &x_scr, &y_scr);
		rt->res.x = (rt->res.x > x_scr) ? x_scr : rt->res.x;
		rt->res.y = (rt->res.y > y_scr) ? y_scr : rt->res.y;
	}
	if (!(rt->win = mlx_new_window(rt->mlx, rt->res.x, rt->res.y, "miniRT")))
		handle_error("fail to create Minilibx window", rt);
	rt->img.img = mlx_new_image(rt->mlx, rt->res.x, rt->res.y);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
							&rt->img.line_length, &rt->img.endian);
}

void		start_minirt(t_scene *rt)
{
	mlx_clear_window(rt->mlx, rt->win);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img, 0, 0);
	mlx_hook(rt->win, 2, 1L << 0, key_hook, rt);
	mlx_hook(rt->win, 17, 1L << 17, exit_program, 0);
	mlx_loop(rt->mlx);
}

int			main(int argc, char **argv)
{
	t_scene	rt;
	int		i;
	int		fd;

	if (argc > 3 || argc == 1 || (argc == 3 &&
								ft_strcmp(argv[2], "--save") != 0))
		handle_error("Wrong arguments", &rt);
	i = open_and_check_error(argv[1], &fd, &rt);
	parse_rt(&rt, argv[1]);
	init_mlx(&rt, argc);
	render_image(&rt);
	ft_printf("Rendered!\n");
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		export_bmp(create_bmp_filename(argv[1], i, &rt), &rt);
		ft_printf("File %.*s.bmp created!\n", (ft_strlen(argv[1]) - 3),
			argv[1]);
	}
	else
		start_minirt(&rt);
	return (1);
}
