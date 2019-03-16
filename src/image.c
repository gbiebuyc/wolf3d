/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:40:06 by nallani           #+#    #+#             */
/*   Updated: 2019/03/16 22:06:10 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	putpixel(t_img *img, int x, int y, uint32_t color)
{
	if (x >= 0 && x < img->w && y >= 0 && y < img->h)
		img->pixels[x + y * img->w] = color;
}

void	put_block(t_img *minimap, double x, double y, int colo)
{
	int		i;
	int		j;

	i = 0;
	x *= SQUARE_W;
	y *= SQUARE_W;
	while (i < SQUARE_W)
	{
		j = 0;
		while (j < SQUARE_W)
		{
			if (!(i == 0 || j == 0 || i == SQUARE_W - 1 || j == SQUARE_W - 1))
				putpixel(minimap, x + i, y + j, colo);
			j++;
		}
		i++;
	}
}

void	refresh_player(t_data *d)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		radius;

	x = d->minimap.w / 2;
	y = d->minimap.h / 2;
	radius = 7;
	dx = -radius;
	while (dx <= radius)
	{
		dy = (int)sqrt(radius * radius - dx * dx);
		while (dy >= 0)
		{
			putpixel(&d->minimap, x + dx, y + dy, 0xFF);
			putpixel(&d->minimap, x + dx, y - dy, 0xFF);
			dy--;
		}
		dx++;
	}
}

void	refresh_minimap(t_data *d)
{
	int		x;
	int		y;
	int		i;

	x = 0;
	i = 0;
	while (i < d->minimap.w * d->minimap.h)
		d->minimap.pixels[i++] = 0x80 << 24;
	refresh_player(d);
	while (x < MINIMAPSIZE + 1)
	{
		y = 0;
		while (y < MINIMAPSIZE + 1)
		{
			if (get_map_char(floor(d->pos.x) + x - MINIMAPSIZE / 2,
						floor(d->pos.y) + y - MINIMAPSIZE / 2, d) !=
					EMPTY_SQUARE)
				put_block(&d->minimap, (double)x - (d->pos.x - floor(d->pos.x)),
						(double)y - (d->pos.y - floor(d->pos.y)), 0x8000FF00);
			y++;
		}
		x++;
	}
}
