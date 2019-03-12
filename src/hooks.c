/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:26:29 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/12 21:45:42 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_press(int keycode, t_data *d)
{
	if (keycode == 65307 || keycode == 53)
		proper_exit(d);
	else if (keycode == 109 || keycode == 46)
		d->hooks.minimap = !(d->hooks.minimap);
	else if (keycode == 122 || keycode == 13)
		d->hooks.dir = FORWARD;
	else if (keycode == 115 || keycode == 1)
		d->hooks.dir = BACKWARD;
	else if (keycode == 113 || keycode == 0)
		d->hooks.strafe_dir = LEFT_STRAFE;
	else if (keycode == 100 || keycode == 2)
		d->hooks.strafe_dir = RIGHT_STRAFE;
	else if (keycode == 65361 || keycode == 123)
		d->hooks.hor_rot = LEFT_ROT;
	else if (keycode == 65363 || keycode == 124)
		d->hooks.hor_rot = RIGHT_ROT;
	else if (keycode == 65364 || keycode == 125) // Down key
		; // ??
	else if (keycode == 65362 || keycode == 126) // Up key
		; // ??
	else if (keycode == 65505 || keycode == 65506 ||
			keycode == 257 || keycode == 258)
		d->hooks.run = 1;
	return (0);
}

int		key_release(int keycode, t_data *d)
{
	if ((keycode == 122 || keycode == 13) && d->hooks.dir == FORWARD)
		d->hooks.dir = 0;
	if ((keycode == 115 || keycode == 1) && d->hooks.dir == BACKWARD)
		d->hooks.dir = 0;
	if ((keycode == 113 || keycode == 0) && d->hooks.strafe_dir == LEFT_STRAFE)
		d->hooks.strafe_dir = 0;
	if ((keycode == 100 || keycode == 2) && d->hooks.strafe_dir == RIGHT_STRAFE)
		d->hooks.strafe_dir = 0;
	else if (keycode == 65361 || keycode == 123 ||
			keycode == 65363 || keycode == 124) // Hor rotate
		d->hooks.hor_rot = 0;
	else if (keycode == 65362 || keycode == 126 ||
			keycode == 65364 || keycode == 125) // Ver rotate
		; // ??
	else if (keycode == 65505 || keycode == 65506 ||
			keycode == 257 || keycode == 258) 
		d->hooks.run = 0;
	return (0);
}

int		mouse_press(int btn, int x, int y, t_data *d)
{
	if (btn == 4 || btn == 5)
	{
		printf("molette\n");
	}
	else if (y > 0)
	{
		d->mouse_btn = btn;
		d->mouse_lastpos = (t_vec2){x, y};
	}
	return (0);
}

int		mouse_release(int btn, int x, int y, t_data *d)
{
	(void)btn;
	(void)x;
	(void)y;
	d->mouse_btn = false;
	return (0);
}

int		mouse_move(int x, int y, t_data *d)
{
	t_vec2		delta;
	static int	oldx;
	static int	oldy;

	if (d->mouse_btn == 1)
	{
		delta = sub_vec2((t_vec2){x, y}, d->mouse_lastpos);
		d->mouse_lastpos = (t_vec2){x, y};
		printf("mouse move %d, %d\n", delta.x, delta.y);
	}
	if (oldx == 0 && oldy == 0) 
	{
		oldx = x;
		oldy = y;
	}
	if (x != oldx)
	{
	actualize_dir(0.0174533 * (x - oldx) / 5, &d->dir);
	actualize_dir(0.0174533 * (x - oldx) / 5, &d->plane);
	}
	if (y != oldy)
	{
		d->hooks.middle_screen -= (y - oldy);
		if (d->hooks.middle_screen < -HEIGHT / 4)
			d->hooks.middle_screen = -HEIGHT / 4;
		if (d->hooks.middle_screen > HEIGHT)
			d->hooks.middle_screen = HEIGHT;
	}
	{
		mlx_mouse_move(d->win, WIDTH / 2, HEIGHT / 2);
		oldx = WIDTH / 2;
		oldy = HEIGHT / 2;
	}
	return (0);	
}
