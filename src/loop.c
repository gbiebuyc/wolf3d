/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:53:08 by nallani           #+#    #+#             */
/*   Updated: 2019/03/12 22:53:05 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	collide(t_vec2 blk, t_data *d)
{
	double	nearest_x;
	double	nearest_y;
	double	dx;
	double	dy;
	double	len;

	if (get_map_char(blk.x, blk.y, d) == EMPTY_SQUARE)
		return ;
	nearest_x = fmax(blk.x, fmin(d->pos.x, blk.x + 1));
	nearest_y = fmax(blk.y, fmin(d->pos.y, blk.y + 1));
	dx = d->pos.x - nearest_x;
	dy = d->pos.y - nearest_y;
	if ((len = vec2f_length((t_vec2f){dx, dy})) > COLLISION_DIST)
		return ;
	d->pos.x = nearest_x + dx * COLLISION_DIST / len;
	d->pos.y = nearest_y + dy * COLLISION_DIST / len;
}

void	move(t_data *d, t_vec2f dir)
{
	d->pos = add_vec2f(d->pos, dir);
	// test collision with 8 surrounding blocks
	collide((t_vec2){floor(d->pos.x) - 1, floor(d->pos.y) - 1}, d);
	collide((t_vec2){floor(d->pos.x) - 0, floor(d->pos.y) - 1}, d);
	collide((t_vec2){floor(d->pos.x) + 1, floor(d->pos.y) - 1}, d);
	collide((t_vec2){floor(d->pos.x) + 1, floor(d->pos.y) - 0}, d);
	collide((t_vec2){floor(d->pos.x) + 1, floor(d->pos.y) + 1}, d);
	collide((t_vec2){floor(d->pos.x) - 0, floor(d->pos.y) + 1}, d);
	collide((t_vec2){floor(d->pos.x) - 1, floor(d->pos.y) + 1}, d);
	collide((t_vec2){floor(d->pos.x) - 1, floor(d->pos.y) - 0}, d);
}

int		refresh_loop_3(t_data *d)
{
	static int	time;
	int			i;

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
	i = NORTH - 1;
	if (!(++time % 2))
		while (++i <= WEST)
		{
			d->textures[1][i] = *d->textures[1][i].next;
			d->textures[2][i] = *d->textures[2][i].next;
		}
	if (time == 1000)
		time = 0;
	refresh_all(d);
	return (0);
}

int		refresh_loop_2(t_data *d, t_vec2f tmp)
{
	if (d->hooks.strafe_dir == RIGHT_STRAFE)
	{
		if (d->hooks.dir == 0)
			actualize_dir(1 * M_PI / 2, &tmp);
		else
			actualize_dir(d->hooks.dir == BACKWARD ?
					-M_PI / 4 : -3 * M_PI / 4, &tmp);
		move(d, mul_vec2f(tmp, (!(d->hooks.dir) ? 0.05 : -0.05) *
					(d->hooks.run ? 2 : 1)));
	}
	if (d->hooks.hor_rot == LEFT_ROT)
	{
		actualize_dir(-0.05, &d->dir);
		actualize_dir(-0.05, &d->plane);
	}
	return (refresh_loop_3(d));
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
	return (refresh_loop_2(d, tmp));
}
