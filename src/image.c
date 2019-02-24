/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:40:06 by nallani           #+#    #+#             */
/*   Updated: 2019/02/24 15:38:28 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_block(uint32_t *minimap, int x, int y, int colo)
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
		minimap[x+i + (y+j) * SQUARE_W * MAPSIZE] = 0; 
			else
		minimap[x+i + (y+j) * SQUARE_W * MAPSIZE] = colo; 
		j++;
		}
		i++;
	}
}

int		find_colo_mini(char block)
{
	if (block == '1')
		return (0xFF00);
	return (0);
}

void	refresh_player(t_data *d)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		radius;

	x = (int)(d->p.pos.x / 10 * SQUARE_W * MAPSIZE);
	y = (int)(d->p.pos.y / 10 * SQUARE_W * MAPSIZE);
	radius = 7;
	dx = -radius;
	while (dx <= radius)
	{
		dy = (int)sqrt(radius*radius - dx*dx);
		while (dy >= 0)
		{
			d->minimappixels[x + dx + (y + dy) * SQUARE_W * MAPSIZE] = 0xFF;
			d->minimappixels[x + dx + (y - dy) * SQUARE_W * MAPSIZE] = 0xFF;
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
	ft_memset(d->minimappixels, 0, SQUARE_W * MAPSIZE * SQUARE_W * MAPSIZE * sizeof(uint32_t));
	refresh_player(d);
	while (x < MAPSIZE)
	{
		y = 0; // a calculer en fonction de la position du joueur voir des bords
		while (y < MAPSIZE)
		{
			if (d->map[x][y] != '0')
			put_block(d->minimappixels, x, y, find_colo_mini(d->map[x][y]));
		y++;
		}
		x++;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->minimapimg, WIDTH - (SQUARE_W
				* MAPSIZE), 0);
}
