/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:16:19 by qrigil            #+#    #+#             */
/*   Updated: 2021/03/22 15:16:25 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <math.h>

# include "../libft/includes/libft.h"
# include "keys.h"
# include "../minilibx/mlx.h"
# include "scene_objects.h"

# define SPHERE 1
# define SQUARE 2
# define CYLINDER 3
# define PLANE 4
# define TRIANGLE 5

# define REF_RAYS 1
# define SHINE 1000
# define REFLECT 0.3
# define BACKGROUND_COLOR 0x00000000
# define HEADER_SIZE 122

typedef struct	s_vars
{
	t_vec		dir;
	t_vec		point;
	t_vec		normal;
	t_elem		*cl_el;
	float		cl_t;
	t_elem		*shadow_elem;
	float		shadow_t;
	float		t1;
	float		t2;

	float		a;
	float		b;
	float		c;
}				t_vars;

typedef struct	s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct	s_scene
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_resol		res;
	t_amb_light	amb;
	t_list		*objs_list;
	t_list		*cams_list;
	t_list		*lights_list;
}				t_scene;

typedef struct	s_intens
{
	float		r;
	float		g;
	float		b;
}				t_intens;

int				parse_rt(t_scene *scene, char *filename);
int				check_split(char **split, int len);
float			ft_atof(char *split);

int				key_hook(int keycode, t_scene *rt);
void			handle_error(char *str, t_scene *rt);
void			free_split(char **line);

void			print_pixel(t_image *data, int x, int y, int color);
void			render_image(t_scene *rt);

t_vec			vec_add(t_vec a, t_vec b);
t_vec			vec_sub(t_vec a, t_vec b);
t_vec			vec_mult(t_vec vec, float num);
t_vec			vec_div(t_vec vec, float num);
t_vec			vec_norm(t_vec vec);
t_vec			vec_cross(t_vec v1, t_vec v2);
float			vec_len(t_vec a);
float			vec_skal(t_vec a, t_vec b);
t_vec			vec_rev(t_vec a);

int				convert_to_int(t_color rgb);
t_color			convert_to_rgb(int color);
t_color			col_intens(t_color rgb, float i);
t_color			col_add(t_color col1, t_color col2, float i);
t_color			col_int(t_color rgb, t_intens i);

t_color			trace_ray(t_scene *rt, t_vec dir, t_vec ori, int depth);
t_vec			reflect_ray(t_vec dir, t_vec norm);
t_vec			calc_ray(t_scene *rt, float fov, float x, float y);
t_intens		lights(t_vars *vars, t_scene *rt, t_vec dir);

void			sphere(t_elem *sphere, t_vec ori, t_vec dir, t_vars *vars);
void			interseption(t_scene *rt, t_vars *vars, t_vec ori, t_vec dir);
void			square(t_elem *square, t_vec ori, t_vec dir, t_vars *vars);
void			plane(t_elem *plane, t_vec ori, t_vec dir, t_vars *vars);
void			triangle(t_elem *tri, t_vec ori, t_vec dir, t_vars *vars);
void			cylinder(t_elem *cyl, t_vec ori, t_vec dir, t_vars *vars);
t_vec			get_cylinder_normal(t_elem *cyl, t_vec p);
void			check_obj(t_elem *elem, t_vec ori, t_vec dir, t_vars *vars);

void			export_bmp(char *filename, t_scene *rt);
char			*create_bmp_filename(char *file, int i, t_scene *rt);
int				open_and_check_error(char *filename, int *fd, t_scene *rt);
int				exit_program(void);

void			rot(t_vec *vec, t_vec *angle);
void			anti_rot(t_vec *vec, t_vec *angle);

t_vec			parse_vec(char *split_line, t_scene *rt, int i);
t_color			parse_rgb(char *split_line, t_scene *rt);
void			parse_cylinder(t_scene *rt, char **split_line);
void			parse_sphere(t_scene *rt, char **split_line);
void			parse_plane(t_scene *rt, char **split_line);
void			parse_square(t_scene *rt, char **split_line);
void			parse_triangle(t_scene *rt, char **split_line);
void			parse_lights(t_scene *rt, char **split_line);
void			parse_cams(t_scene *rt, char **split_line);
void			parse_amb(t_scene *rt, char **split_line);
void			parse_resol(t_scene *rt, char **split_line);

t_vec			calculate_direction(t_cam *cam, t_scene *rt, float x, float y);
void			calculate_axis(t_cam *cam);

void			matrix_free(float **matrix);
t_vec			matrix_mult(float **matrix, t_vec vec);
float			**matrix_create(t_cam *cam);
#endif
