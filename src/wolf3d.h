/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:58:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/22 17:16:51 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <libft.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <stdbool.h>

# include <stdio.h> // for debug

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

typedef struct	s_state
{
	void		*mlx;
	void		*win;
	void		*img;
	uint32_t	*pixels;
	int			mouse_btn;
	t_vec2		mouse_lastpos;
}				t_data;

# define WIDTH 1024
# define HEIGHT 768

int				key_press(int keycode, t_data *st);
int				mouse_press(int btn, int x, int y, t_data *st);
int				mouse_release(int btn, int x, int y, t_data *st);
int				mouse_move(int x, int y, t_data *st);
int				destroy_event(t_data *st);
int				loop_hook(t_data *st);
t_vec2			sub_vec2(t_vec2 v1, t_vec2 v2);
t_vec2			add_vec2(t_vec2 v1, t_vec2 v2);

#endif
