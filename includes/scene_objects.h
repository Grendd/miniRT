/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sceneObjects.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:16:47 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 15:16:51 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_SCENE_OBJECTS_H
# define MINIRT_SCENE_OBJECTS_H

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef struct	s_resol
{
	int			x;
	int			y;
}				t_resol;

typedef struct	s_amb_light
{
	float		ratio;
	t_color		rgb;
}				t_amb_light;

typedef struct	s_cam
{
	t_vec		coords;
	t_vec		orient;
	int			fov;

	t_vec		up;
	t_vec		right;
	t_vec		forward;
}				t_cam;

typedef struct	s_light
{
	t_vec		coords;
	float		ratio;
	t_color		rgb;
}				t_light;

typedef struct	s_elem
{
	int			type;
	t_vec		coords;
	t_color		rgb;

	t_vec		norm;
	float		diameter;
	float		height;
	float		side_size;

	t_vec		t1;
	t_vec		t2;
	t_vec		t3;
}				t_elem;
#endif
