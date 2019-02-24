/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:26:29 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/24 21:09:05 by nallani          ###   ########.fr       */
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
	printf("x: %f\ny: %f\n", dir->x, dir->y);
}
/*
** fin a supp
*/
int		key_press(int keycode, t_data *d)
{
	if (keycode == 65307 || keycode == 53)
	{
		mlx_destroy_image(d->mlx, d->img);
		mlx_destroy_window(d->mlx, d->win);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 65361 || keycode == 123)
		actualize_dir(-0.174, &(d->p.dir));
	else if (keycode == 65362 || keycode == 126)
		d->p.pos = sub_vec2f(d->p.pos, d->p.dir);// Arriere
	else if (keycode == 65363 || keycode == 124)
		actualize_dir(0.174, &(d->p.dir));
	else if (keycode == 65364 || keycode == 125)
		d->p.pos = add_vec2f(d->p.pos, d->p.dir);// Avant
	refresh_minimap(d);
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
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->win);
	exit(EXIT_SUCCESS);
	return (0);
}
