/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:26:29 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/06 04:58:44 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define ARROW_SENSITIVITY 0.2

/*
**  fonction suivante a changer de fichier
*/

void	actualize_dir(double diff, t_vec2f *dir)
{
	double	x;
	double	y;

	x = dir->x;
	y = dir->y;
	dir->x = x * cos(diff) - y * sin(diff);
	dir->y = x * sin(diff) + y * cos(diff);
}
/*
** fin a supp
*/

# define COLLISION_DIST 0.2 // max 0.5 car c'est la moitie d'un bloc.

void	move(t_data *d, t_vec2f dir)
{	
	if (fabs(dir.x) > fabs(dir.y))
	{
		d->pos.x += dir.x;
		if (get_map_char(d->pos.x + (dir.x > 0 ? COLLISION_DIST : -COLLISION_DIST),
					d->pos.y + (dir.y > 0 ?
						-COLLISION_DIST : COLLISION_DIST), d) != EMPTY_SQUARE)
			d->pos.x = (dir.x > 0) ?
				ceil(d->pos.x - dir.x) - COLLISION_DIST : floor(d->pos.x - dir.x) + COLLISION_DIST;
		d->pos.y += dir.y;
		if (get_map_char(d->pos.x, d->pos.y + (dir.y > 0 ?
						COLLISION_DIST : -COLLISION_DIST), d) != EMPTY_SQUARE)
			d->pos.y = (dir.y > 0) ?
				ceil(d->pos.y - dir.y) - COLLISION_DIST : floor(d->pos.y - dir.y) + COLLISION_DIST;
	}
	else
	{
		d->pos.y += dir.y;
		if (get_map_char(d->pos.x, d->pos.y + (dir.y > 0 ?
						COLLISION_DIST : -COLLISION_DIST), d) != EMPTY_SQUARE)
			d->pos.y = (dir.y > 0) ?
				ceil(d->pos.y - dir.y) - COLLISION_DIST : floor(d->pos.y - dir.y) + COLLISION_DIST;
		d->pos.x += dir.x;
		if (get_map_char(d->pos.x + (dir.x > 0 ? COLLISION_DIST : -COLLISION_DIST),
					d->pos.y + (dir.y > 0 ?
						COLLISION_DIST : -COLLISION_DIST), d) != EMPTY_SQUARE)
			d->pos.x = (dir.x > 0) ?
				ceil(d->pos.x - dir.x) - COLLISION_DIST : floor(d->pos.x - dir.x) + COLLISION_DIST;
	}
/*	if (get_map_char(d->pos.x + (dir.x > 0 ? COLLISION_DIST : -COLLISION_DIST),
				d->pos.y, d) != EMPTY_SQUARE)
{
		d->pos.x = (dir.x > 0) ?
			ceil(d->pos.x - dir.x) - COLLISION_DIST : floor(d->pos.x - dir.x) + COLLISION_DIST;
		return ;
}
	if (get_map_char(d->pos.x, d->pos.y + (dir.y > 0 ?
				COLLISION_DIST : -COLLISION_DIST), d) != EMPTY_SQUARE)
		d->pos.y = (dir.y > 0) ?
			ceil(d->pos.y - dir.y) - COLLISION_DIST : floor(d->pos.y - dir.y) + COLLISION_DIST;
*/}

int		key_press(int keycode, t_data *d)
{
	if (keycode == 65307 || keycode == 53)
		proper_exit(d);
	else if (keycode == 109 || keycode == 46)
		d->hooks.minimap = !(d->hooks.minimap); // GERER TRACE RAYON // COM A NE PAS SUPP
	else if (keycode == 122 || keycode == 13) // Avant
		d->hooks.dir = FORWARD;
	else if (keycode == 115 || keycode == 1) // Arriere
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
		;
	else if (keycode == 65362 || keycode == 126) // Up key
		;
	else if (keycode == 65505 || keycode == 65506 ||
			keycode == 257 || keycode == 258) // both shift
		d->hooks.run = 1;
	return (0);
}

int		key_release(int keycode, t_data *d)
{
	if ((keycode == 122 || keycode == 13) && d->hooks.dir == FORWARD) // Avant
		d->hooks.dir = 0;
	if ((keycode == 115 || keycode == 1) && d->hooks.dir == BACKWARD) // Arriere
		d->hooks.dir = 0;
	if ((keycode == 113 || keycode == 0) && d->hooks.strafe_dir == LEFT_STRAFE) //gauche
		d->hooks.strafe_dir = 0;
	if ((keycode == 100 || keycode == 2) && d->hooks.strafe_dir == RIGHT_STRAFE) //droite
		d->hooks.strafe_dir = 0;
	else if (keycode == 65361 || keycode == 123 ||
			keycode == 65363 || keycode == 124) // Hor rotate
		d->hooks.hor_rot = 0;
	else if (keycode == 65362 || keycode == 126 ||
			keycode == 65364 || keycode == 125) // Ver rotate
		;
	else if (keycode == 65505 || keycode == 65506 ||
			keycode == 257 || keycode == 258) // Run
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

int		refresh_loop(t_data *d)
{
	t_vec2f		tmp;

	tmp = d->dir;
	if (d->hooks.dir == FORWARD && d->hooks.strafe_dir == 0)
		move(d, mul_vec2f(d->dir, 0.05 * (d->hooks.run ? 2 : 1)));
	if (d->hooks.dir == BACKWARD && d->hooks.strafe_dir == 0)
		move(d, mul_vec2f(d->dir, -0.05 * (d->hooks.run ? 2 : 1)));
	if (d->hooks.strafe_dir == LEFT_STRAFE)
	{
		if (d->hooks.dir == 0)
			actualize_dir(-M_PI / 2, &tmp);
		else
			actualize_dir(d->hooks.dir == FORWARD ?
					-M_PI / 4 : -3 * M_PI / 4, &tmp);
		move(d, mul_vec2f(tmp, 0.05 * (d->hooks.run ? 2 : 1)));
	}
	if (d->hooks.strafe_dir == RIGHT_STRAFE)
	{
		if (d->hooks.dir == 0)
			actualize_dir(1 * M_PI / 2, &tmp);
		else
			actualize_dir(d->hooks.dir == BACKWARD ?
					-M_PI / 4 : -3 * M_PI / 4, &tmp);
		move(d, mul_vec2f(tmp,(!(d->hooks.dir) ? 0.05: -0.05) * (d->hooks.run ? 2 : 1)));
	}
	if (d->hooks.hor_rot == LEFT_ROT)
	{
		actualize_dir(-0.05, &d->dir);
		actualize_dir(-0.05, &d->plane);
	}
	if (d->hooks.hor_rot == RIGHT_ROT)
	{
		actualize_dir(0.05, &d->dir);
		actualize_dir(0.05, &d->plane);
	}
	d->hooks.scroll.x += SCROLL_SPEED;
	d->hooks.scroll.y += SCROLL_SPEED / 4;
	if ((int)d->hooks.scroll.x == 1)
		d->hooks.scroll.x = 0;
	if ((int)d->hooks.scroll.y == 1)
		d->hooks.scroll.y = 0;
//	if (d->hooks.strafe_dir == RIGHT_STRAFE)
//	{
//		if (d->hooks.dir == 0)
//			actualize_dir(M_PI / 2, &tmp);
//		else
//			actualize_dir(d->hooks.dir == FORWARD ?
//					M_PI / 4 : 3 * M_PI / 4, &tmp);
//		actualize_dir(-M_PI / 2, &tmp);
//		move(d, mul_vec2f(tmp, -0.05));
//	}
	refresh_all(d);
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
	oldx = x;
	}
	if (y != oldy)
	{
		d->hooks.middle_screen -= (y - oldy);
		if (d->hooks.middle_screen < -HEIGHT / 4)
			d->hooks.middle_screen = -HEIGHT / 4;
		if (d->hooks.middle_screen > HEIGHT)
			d->hooks.middle_screen = HEIGHT;
		oldy = y;
	}
	if (x <= 0 || y < -20 || x > WIDTH || y > HEIGHT)
	{
		mlx_mouse_move(d->win, WIDTH / 2, HEIGHT / 2);
	oldx = WIDTH / 2;
	oldy = HEIGHT / 2;
	// besoin de la position de la fenetre pour centrer
	}
	return (0);	
}
