/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:26:29 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/03 23:03:44 by gbiebuyc         ###   ########.fr       */
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
		destroy_event(d);
	if (keycode == 65361 || keycode == 123)
	{
		actualize_dir(-0.174533, &d->dir);
		actualize_dir(-0.174533, &d->plane);
	}
	else if (keycode == 65362 || keycode == 126) // Avant
		move(d, mul_vec2f(d->dir, 0.2));
	else if (keycode == 65363 || keycode == 124)
	{
		actualize_dir(0.174533, &d->dir);
		actualize_dir(0.174533, &d->plane);
	}
	else if (keycode == 65364 || keycode == 125) // Arriere
		move(d, mul_vec2f(d->dir, -0.2));
	refresh_all(d);
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

	if (d->mouse_btn == 1)
	{
		delta = sub_vec2((t_vec2){x, y}, d->mouse_lastpos);
		d->mouse_lastpos = (t_vec2){x, y};
		printf("mouse move %d, %d\n", delta.x, delta.y);
	}
	return (0);
}

int		destroy_event(t_data *d)
{
	mlx_destroy_image(d->mlx, d->camera.mlximg);
	mlx_destroy_image(d->mlx, d->minimap.mlximg);
	mlx_destroy_window(d->mlx, d->win);
	exit(EXIT_SUCCESS);
	return (0);
}
