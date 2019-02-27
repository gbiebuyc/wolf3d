/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:40:06 by nallani           #+#    #+#             */
/*   Updated: 2019/02/27 04:39:13 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	putpixel(t_img *img, int x, int y, uint32_t color)
{
	static bool printed_warning;

	if (x >= 0 && x < img->w && y >= 0 && y < img->h)
		img->pixels[x + y * img->w] = color;
	else if (!printed_warning)
	{
		ft_putstr("pixel outside image\n");
		printed_warning = true;
	}
}

void	put_block(t_img *minimap, int x, int y, int colo)
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
	printf("debug find_colo%c\n", block);
	return (0);
}

void	refresh_player(t_data *d)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		radius;

	x = (int)(d->pos.x * SQUARE_W);
	y = (int)(d->pos.y * SQUARE_W);
	radius = 7;
	dx = -radius;
	while (dx <= radius)
	{
		dy = (int)sqrt(radius*radius - dx*dx);
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

	x = 0; // a calculer en fonction de la position du joueur voir des bords
	ft_memset(d->minimap.pixels, 0, d->minimap.w * d->minimap.h * sizeof(uint32_t));
	refresh_player(d);
	while (x < d->mapsize.x)
	{
		y = 0; // a calculer en fonction de la position du joueur voir des bords
		while (y < d->mapsize.y)
		{
			if (d->map[x + y * d->mapsize.y] != EMPTY_SQUARE)
				put_block(&d->minimap, x, y,
						find_colo_mini(d->map[x + y * d->mapsize.y]));
			y++;
		}
		x++;
	}
	//mlx_put_image_to_window(d->mlx, d->win, d->minimap.mlximg, WIDTH - d->minimap.w, 0);
}
