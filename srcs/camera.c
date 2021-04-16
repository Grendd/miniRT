/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:57:58 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:58:01 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void		matrix_free(float **matrix)
{
	int		i;

	i = -1;
	while (++i < 4)
		free(matrix[i]);
	free(matrix);
	matrix = 0;
}

void		calculate_axis(t_cam *cam)
{
	t_vec	temp;

	temp = (t_vec){0, 1, 0};
	if (cam->orient.x == 0 && cam->orient.y != 0 && cam->orient.z == 0)
		cam->orient.x = 0.0001;
	cam->forward = vec_norm(vec_mult(cam->orient, -1));
	cam->right = vec_norm(vec_cross(temp, cam->forward));
	cam->up = vec_norm(vec_cross(cam->forward, cam->right));
}

void		matrix_fill(t_cam *cam, float **matrix)
{
	matrix[0][0] = cam->right.x;
	matrix[0][1] = cam->right.y;
	matrix[0][2] = cam->right.z;
	matrix[1][0] = cam->up.x;
	matrix[1][1] = cam->up.y;
	matrix[1][2] = cam->up.z;
	matrix[2][0] = cam->forward.x;
	matrix[2][1] = cam->forward.y;
	matrix[2][2] = cam->forward.z;
}

float		**matrix_create(t_cam *cam)
{
	float	**matrix;
	int		i;

	if (!(matrix = (float**)malloc(sizeof(float*) * 4)))
		return (NULL);
	i = -1;
	while (++i < 4)
		if (!(matrix[i] = (float*)malloc(sizeof(float) * 4)))
			return (NULL);
	matrix_fill(cam, matrix);
	return (matrix);
}

t_vec		matrix_mult(float **matrix, t_vec vec)
{
	t_vec	dir;

	dir.x = vec.x * matrix[0][0] + vec.y * matrix[1][0] + vec.z * matrix[2][0];
	dir.y = vec.x * matrix[0][1] + vec.y * matrix[1][1] + vec.z * matrix[2][1];
	dir.z = vec.x * matrix[0][2] + vec.y * matrix[1][2] + vec.z * matrix[2][2];
	return (dir);
}
