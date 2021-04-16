/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:57:05 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 14:57:09 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void				fill_bmp(char **data, t_scene *rt)
{
	int				i;
	int				j;
	int				x;
	int				y;

	i = HEADER_SIZE;
	y = rt->res.y;
	while (y--)
	{
		x = -1;
		while (++x < rt->res.x)
		{
			j = (x * (rt->img.bits_per_pixel / 8)) + (y * rt->img.line_length);
			*(*data + i++) = *(rt->img.addr + j++);
			*(*data + i++) = *(rt->img.addr + j++);
			*(*data + i++) = *(rt->img.addr + j);
		}
	}
}

void				header_bmp(char **data, t_scene *rt)
{
	unsigned int	size;

	size = rt->res.y * rt->res.x * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + HEADER_SIZE);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = HEADER_SIZE;
	*(unsigned int *)(*data + 14) = HEADER_SIZE - 14;
	*(unsigned int *)(*data + 18) = rt->res.x;
	*(unsigned int *)(*data + 22) = rt->res.y;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

void				export_bmp(char *filename, t_scene *rt)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	char			*data;

	size = rt->res.y * rt->res.x * 3;
	if (!(data = malloc((size + HEADER_SIZE))))
		handle_error("Can't open file", rt);
	i = 0;
	while (i < size + HEADER_SIZE)
		data[i++] = 0;
	header_bmp(&data, rt);
	fill_bmp(&data, rt);
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		handle_error("Can't create file", rt);
	write(fd, data, (size + HEADER_SIZE));
	close(fd);
}

char				*create_bmp_filename(char *file, int i, t_scene *rt)
{
	char			*filename;
	int				n;

	if (!(filename = malloc(sizeof(char) * (i + 5))))
		handle_error("Can't malloc filename", rt);
	n = -1;
	while (++n <= i)
		*(filename + n) = *(file + n);
	*(unsigned int *)(filename + n) =
			*(const unsigned int *)(unsigned long)"bmp\0";
	return (filename);
}

int					open_and_check_error(char *filename, int *fd, t_scene *rt)
{
	int				i;

	if ((*fd = open(filename, O_RDONLY)) <= 0)
		handle_error("Can't open file", rt);
	i = 0;
	while (filename[i] != '.' && filename[i])
		i++;
	if (!filename[i])
		handle_error("Can't read filename", rt);
	if (i < 3 || ft_strcmp(&filename[i], ".rt") != 0)
		handle_error("Wrong extension", rt);
	return (i);
}
