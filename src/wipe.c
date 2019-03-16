/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 23:03:28 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/16 03:34:26 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Perlin noise number sequence
*/

int		get_random_offset(int x)
{
	return ((uint8_t[]){0, 1, 2, 1, 1, 2, 3, 2, 3, 4, 5, 6, 6, 5, 5, 6, 7, 8, 8,
			7, 8, 7, 7, 8, 10, 11, 10, 11, 12, 12, 11, 11, 11, 11, 12, 11, 10,
			11, 11, 10, 10, 10, 8, 8, 7, 7, 7, 8, 8, 7, 7, 8, 10, 11, 11, 12,
			11, 10, 10, 8, 10, 10, 10, 10, 8, 8, 8, 10, 8, 10, 11, 10, 10, 11,
			10, 10, 8, 7, 6, 7, 8, 10, 10, 10, 10, 11, 10, 10, 11, 11, 10, 10,
			11, 12, 11, 11, 11, 12, 11, 10, 11, 10, 8, 7, 6, 5, 5, 6, 5, 6, 6,
			7, 8, 7, 7, 6, 7, 7, 6, 6, 5, 4, 5, 5, 4, 4, 4, 4, 4, 5, 5, 5, 4, 3,
			2, 2, 1, 1, 2, 3, 3, 3, 4, 5, 6, 7, 6, 7, 6, 7, 6, 6, 5, 5, 6, 6, 7,
			8, 8, 8}[x * 160 / WIDTH] * 20);
}

# define RANDOM_RANGE 240
# define WIPE_SPEED (HEIGHT / 20)

void	wipe(t_data *d)
{
	int	x;
	int	y1;
	int	y2;

	x = 0;
	while (x < WIDTH)
	{
		y1 = ft_max(0, d->wipe_offset - get_random_offset(x));
		y2 = 0;
		while (y1 < HEIGHT)
			putpixel(&d->camera, x, y1++,
					d->framebuf2[x + y2++ * WIDTH]);
		x++;
	}
	d->wipe_offset += WIPE_SPEED;
	if (d->wipe_offset >= HEIGHT + RANDOM_RANGE)
	{
		d->wipe_offset = 0;
		d->gamestate = RACE;
	}
}
