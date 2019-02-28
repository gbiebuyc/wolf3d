/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:58:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/28 05:22:31 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <libft.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <stdbool.h>

# include <stdio.h> // for debug

# define WIDTH 1024
# define HEIGHT 768
# define SQUARE_DIST 100
# define SQUARE_W 32
# define GROUND_COLOR 0x9370DB
# define SKY_COLOR 0x00CED1
# define WALL_CHAR '1'
# define EMPTY_SQUARE ' '

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
}				t_inter; // retour find_intersection, contient le char, longueur (rajouter endroit touche ?)

typedef struct	s_img
{
	int			w;
	int			h;
	uint32_t	*pixels;
	void		*mlximg;
}				t_img;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		camera;
	t_img		minimap;
	int			mouse_btn;
	t_vec2		mouse_lastpos;
	char		*map;
	t_vec2		mapsize;
	t_vec2f		pos;
	t_vec2f		dir;
	t_vec2f		plane;
}				t_data;


int				key_press(int keycode, t_data *d);
int				mouse_press(int btn, int x, int y, t_data *d);
int				mouse_release(int btn, int x, int y, t_data *d);
int				mouse_move(int x, int y, t_data *d);
int				destroy_event(t_data *d);
int				loop_hook(t_data *d);
t_vec2			sub_vec2(t_vec2 v1, t_vec2 v2);
t_vec2			add_vec2(t_vec2 v1, t_vec2 v2);
t_vec2f			sub_vec2f(t_vec2f v1, t_vec2f v2);
t_vec2f			add_vec2f(t_vec2f v1, t_vec2f v2);
t_vec2f			mul_vec2f(t_vec2f v, double scalar);
float			get_vec2f_length(t_vec2f v);
void			refresh_minimap(t_data *d);
void			draw_ray(t_img *img, t_vec2f v1, t_vec2f v2, uint32_t color);
void			putpixel(t_img *img, int x, int y, uint32_t color);
t_vec2			convert_vec2f(t_vec2f v);
void			refresh_all(t_data *d);
void			actualize_dir(double angle, t_vec2f *vec);
int				destroy_event(t_data *d);
t_inter			find_intersection_hor(t_vec2f ray, t_data *d);
t_inter			find_intersection_ver(t_vec2f ray, t_data *d);
double			get_vec2f_angle(t_vec2f v1, t_vec2f v2);

#endif
