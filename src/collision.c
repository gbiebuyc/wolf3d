/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 20:49:22 by nallani           #+#    #+#             */
/*   Updated: 2019/03/15 20:49:45 by nallani          ###   ########.fr       */
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
	if (d->gamestate == RACE)
		d->gamestate = GAMEOVER;
}

void	move(t_data *d, t_vec2f dir)
{
	d->pos = add_vec2f(d->pos, dir);
	collide((t_vec2){floor(d->pos.x) - 1, floor(d->pos.y) - 1}, d);
	collide((t_vec2){floor(d->pos.x) - 0, floor(d->pos.y) - 1}, d);
	collide((t_vec2){floor(d->pos.x) + 1, floor(d->pos.y) - 1}, d);
	collide((t_vec2){floor(d->pos.x) + 1, floor(d->pos.y) - 0}, d);
	collide((t_vec2){floor(d->pos.x) + 1, floor(d->pos.y) + 1}, d);
	collide((t_vec2){floor(d->pos.x) - 0, floor(d->pos.y) + 1}, d);
	collide((t_vec2){floor(d->pos.x) - 1, floor(d->pos.y) + 1}, d);
	collide((t_vec2){floor(d->pos.x) - 1, floor(d->pos.y) - 0}, d);
}
