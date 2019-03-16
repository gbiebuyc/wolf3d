/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:53:08 by nallani           #+#    #+#             */
/*   Updated: 2019/03/16 00:02:52 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		refresh_loop_3(t_data *d, short i, int *time)
{
	if (d->hooks.hor_rot == RIGHT_ROT && d->gamestate != GAMEOVER &&
			d->gamestate != WIPESCREEN)
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
	if (!(*time % 2))
		while (++i <= WEST)
		{
			d->textures[3][i] = *d->textures[3][i].next;
			d->textures[1][i] = *d->textures[1][i].next;
			d->textures[2][i] = *d->textures[2][i].next;
		}
	if ((*time %= 10) == 0 && d->gamestate == RACE)
		d->score++;
	refresh_all(d);
	if (d->gamestate == RACE || d->gamestate == GAMEOVER)
		mlx_string_put(d->mlx, d->win, 30, 20, 0xFFFFFF,
				ft_itoa_static(d->score));
	if (d->gamestate == WIPESCREEN)
		wipe(d);
	return (0);
}

void	racing_time(t_data *d, t_vec2f tmp)
{
	t_vec2f		tmp2;

	tmp2 = d->dir;
	if (d->hooks.strafe_dir == RIGHT_STRAFE)
		actualize_dir(1 * M_PI / 2, &tmp);
	if (d->hooks.strafe_dir == LEFT_STRAFE)
		actualize_dir(-M_PI / 2, &tmp);
	tmp2 = mul_vec2f(tmp2, 0.125);
	tmp = mul_vec2f(tmp, 0.05);
	move(d, add_vec2f(d->hooks.strafe_dir ? tmp : (t_vec2f){0, 0}, tmp2));
}

int		refresh_loop_2(t_data *d, t_vec2f tmp)
{
	static int	time;

	time++;
	if (d->hooks.strafe_dir == RIGHT_STRAFE && (d->gamestate == PLAY))
	{
		if (d->hooks.dir == 0)
			actualize_dir(1 * M_PI / 2, &tmp);
		else
			actualize_dir(d->hooks.dir == BACKWARD ?
					-M_PI / 4 : -3 * M_PI / 4, &tmp);
		move(d, mul_vec2f(tmp, (!(d->hooks.dir) ? 0.05 : -0.05) *
					(d->hooks.run ? 2 : 1)));
	}
	if (d->gamestate == RACE)
		racing_time(d, tmp);
	if (d->hooks.hor_rot == LEFT_ROT && d->gamestate != GAMEOVER &&
			d->gamestate != WIPESCREEN)
	{
		actualize_dir(-0.05, &d->dir);
		actualize_dir(-0.05, &d->plane);
	}
	return (refresh_loop_3(d, NORTH - 1, &time));
}

int		refresh_loop(t_data *d)
{
	t_vec2f		tmp;

	tmp = d->dir;
	if (d->hooks.dir == FORWARD && d->hooks.strafe_dir == 0 &&
			(d->gamestate == PLAY))
		move(d, mul_vec2f(d->dir, 0.05 * (d->hooks.run ? 2 : 1)));
	if (d->hooks.dir == BACKWARD && d->hooks.strafe_dir == 0 &&
			(d->gamestate == PLAY))
		move(d, mul_vec2f(d->dir, -0.05 * (d->hooks.run ? 2 : 1)));
	if (d->hooks.strafe_dir == LEFT_STRAFE && (d->gamestate == PLAY))
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
