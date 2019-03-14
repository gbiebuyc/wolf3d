/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:58:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/14 19:22:48 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <libft.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <pthread.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>

# define WIDTH 1024
# define HEIGHT 768
# define SQUARE_DIST 100
# define SQUARE_W 32
# define WALL_CHAR '1'
# define EMPTY_SQUARE ' '
# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3
# define FORWARD 1
# define BACKWARD 2
# define LEFT_STRAFE 3
# define RIGHT_STRAFE 4
# define LEFT_ROT 1
# define RIGHT_ROT 2
# define PATH "./maps/map1"
# define GOOD_CHARS " 1234"
# define SCROLL_SPEED 0.003
# define MINIMAPSIZE 8
# define MAX_SIZE_OF_PATH 150
# define MAX_ANIM 2
# define SF_FRAMES 22
# define PIKA_FRAMES 4
# define ARROW_SENSITIVITY 0.2
# define COLLISION_DIST 0.2

typedef struct	s_var
{
	int			start;
	int			y;
	int			scaled_width;
	double		increment;
	double		real_y;
}				t_var;

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_vec2f
{
	double		x;
	double		y;
}				t_vec2f;

typedef struct	s_inter
{
	float		l;
	char		c;
	t_vec2f		vec;
	int			orientation;
	double		xtexture;
}				t_inter;

typedef struct	s_img
{
	int				w;
	int				h;
	uint32_t		*pixels;
	void			*mlximg;
	struct s_img	*next;
}				t_img;

typedef	struct	s_hooks
{
	char		dir;
	char		strafe_dir;
	char		hor_rot;
	char		minimap;
	int			middle_screen;
	char		run;
	t_vec2f		scroll;
}				t_hook;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		camera;
	t_img		minimap;
	char		*map;
	t_vec2		mapsize;
	t_vec2f		pos;
	t_vec2f		dir;
	t_vec2f		plane;
	t_img		textures[4][4];
	t_img		sky_texture;
	t_hook		hooks;
	uint32_t	fog_color;
	t_img		*anim[3];
}				t_data;

typedef	struct	s_args
{
	t_data		*d;
	t_vec2f		ray_dir;
	int			x;
	double		angle;
	float		dist;
	t_inter		inter[2];
}				t_args;

typedef struct	s_exit_count
{
	short		max_anim;
	short		max_frames[MAX_ANIM];
}				t_exit_count;

/*
** multithread.c
*/
void			refresh_image(t_data *d);
void			draw_column(t_data *d, int block_h, int x, t_inter inter);
void			refresh_all(t_data *d);
/*
** main_image.c
*/
void			draw_sky_and_floor(t_data *d, t_args inf, int block_h);
/*
** image.c
*/
void			refresh_minimap(t_data *d);
void			putpixel(t_img *img, int x, int y, uint32_t color);
/*
** map.c
*/
void			init_map(t_data *d, char *tab, int cout, int fd);
/*
** fog.c
*/
uint32_t		calculate_fog(int y, int max_y, uint32_t fog_color, uint32_t p);
/*
** ray.c
*/
void			draw_ray(t_data *d, t_vec2f v2, uint32_t color);
t_inter			find_intersection_hor(t_vec2f ray, t_data *d);
t_inter			find_intersection_ver(t_vec2f ray, t_data *d);
char			get_map_char(int x, int y, t_data *d);
/*
** hooks.c
*/
int				key_press(int keycode, t_data *d);
int				key_release(int keycode, t_data *d);
int				mouse_move(int x, int y, t_data *d);
/*
** exit.c
*/
int				proper_exit(t_data *d);
void			err_exit(t_data *d, int mod, char *msg, int exit_code);
/*
** texture.c
*/
void			load_textures(t_data *d);
/*
** texture_anim.c
*/
char			*get_xpm_pos(int i, char *path);
void			anim_ryu(t_data *d);
void			anim_pika(t_data *d);
void			duplicate_faces(t_img *img);
t_img			*new_anim(t_data *d, short nb_of_frames, char *path, int junk);
/*
** loop.c
*/
int				refresh_loop(t_data *d);
/*
** vec2.c
*/
t_vec2			sub_vec2(t_vec2 v1, t_vec2 v2);
t_vec2f			sub_vec2f(t_vec2f v1, t_vec2f v2);
t_vec2f			add_vec2f(t_vec2f v1, t_vec2f v2);
void			actualize_dir(double angle, t_vec2f *vec);
/*
** vec2_2.c
*/
t_vec2f			mul_vec2f(t_vec2f v, double scalar);
float			get_vec2f_length(t_vec2f v);
double			vec2f_length(t_vec2f v);
double			get_vec2f_angle(t_vec2f v1, t_vec2f v2);
t_vec2			convert_vec2f(t_vec2f v);

#endif
