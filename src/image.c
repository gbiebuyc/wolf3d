/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:40:06 by nallani           #+#    #+#             */
/*   Updated: 2019/03/14 17:45:52 by nallani          ###   ########.fr       */
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
			if (i == 0 || j == 0 || i == SQUARE_W - 1 || j == SQUARE_W - 1)
				putpixel(minimap, x + i, y + j, 0);
			else
				putpixel(minimap, x + i, y + j, colo);
			j++;
		}
		i++;
	}
}

int		find_colo_mini(char block)
{
	if (block == WALL_CHAR)
		return (0xFF00);
	if (block == '2')
		return (0xFF);
	if (block == '3')
		return (0xCC7700);
	return (0);
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

	x = 0;
	ft_memset(d->minimap.pixels, 0, d->minimap.w * d->minimap.h *
			sizeof(uint32_t));
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
						(double)y - (d->pos.y - floor(d->pos.y)), 0xFF00);
			y++;
		}
		x++;
	}
}
