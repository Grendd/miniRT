/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:59:32 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:59:33 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	handle_error(char *str, t_scene *rt)
{
	ft_printf("Error >> %s <<\n", str);
	ft_lstclear(&rt->objs_list, free);
	ft_lstclear(&rt->cams_list, free);
	ft_lstclear(&rt->lights_list, free);
	rt->objs_list = 0;
	rt->cams_list = 0;
	rt->lights_list = 0;
	exit(EXIT_FAILURE);
}

int		exit_program(void)
{
	exit(0);
}
