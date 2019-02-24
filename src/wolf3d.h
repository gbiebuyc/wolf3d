/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:58:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/24 21:15:46 by nallani          ###   ########.fr       */
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

typedef struct	s_player
{
	t_vec2f		pos;
	t_vec2f		dir;
}				t_player;

typedef struct	s_img
{
	int			w;
	int			h;
	uint32_t	*pixels;
	void		*img;
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
	t_player	p;
}				t_data;


int				key_press(int keycode, t_data *d);
int				mouse_press(int btn, int x, int y, t_data *d);
int				mouse_release(int btn, int x, int y, t_data *d);
int				mouse_move(int x, int y, t_data *d);
int				destroy_event(t_data *d);
int				loop_hook(t_data *d);
t_vec2			sub_vec2(t_vec2 v1, t_vec2 v2);
t_vec2			add_vec2(t_vec2 v1, t_vec2 v2);
t_vec2f			sub_vec2f(t_vec2f v1, t_vec2f v2); //test
t_vec2f			add_vec2f(t_vec2f v1, t_vec2f v2); //test
void			refresh_minimap(t_data *d);

#endif
