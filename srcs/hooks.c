/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:58:46 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:58:48 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

int				key_hook(int keycode, t_scene *rt)
{
	t_list		*curr;

	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W)
		((t_cam*)rt->cams_list->content)->coords.z++;
	if (keycode == KEY_S)
		((t_cam*)rt->cams_list->content)->coords.z--;
	if (keycode == KEY_D)
		((t_cam*)rt->cams_list->content)->coords.x--;
	if (keycode == KEY_A)
		((t_cam*)rt->cams_list->content)->coords.x++;
	if (keycode == KEY_TAB && rt->cams_list->next)
	{
		free(rt->cams_list->content);
		curr = rt->cams_list;
		rt->cams_list = (t_list *)rt->cams_list->next;
		free(curr);
	}
	render_image(rt);
	mlx_clear_window(rt->mlx, rt->win);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.img, 0, 0);
	return (0);
}
