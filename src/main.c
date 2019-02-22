/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:00:33 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/22 19:46:21 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_mlx(t_data *d)
{
	int		junk;

	if (!(d->mlx = mlx_init()) ||
			!(d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "wolf3d")) ||
			!(d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT)) ||
			!(d->pixels = (uint32_t*)mlx_get_data_addr(
					d->img, &junk, &junk, &junk)) ||
			!(d->minimapimg = mlx_new_image(d->mlx, SQUARE_W * MAPSIZE, SQUARE_W * MAPSIZE)) ||
			!(d->minimappixels = (uint32_t*)mlx_get_data_addr(d->minimapimg,
				&junk, &junk, &junk)))
	{
		ft_putstr_fd("rip mlx\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	mlx_hook(d->win, 2, 1L << 0, key_press, d);
	mlx_hook(d->win, 4, 1L << 2, mouse_press, d);
	mlx_hook(d->win, 5, 1L << 3, mouse_release, d);
	mlx_hook(d->win, 6, 1L << 6, mouse_move, d);
	mlx_hook(d->win, 17, 1L << 17, destroy_event, d);
}

void	init_map(t_data *d)
{
	int i;	
	int j;	

	i = 0;
	while (i < MAPSIZE)
	{
		j = 0;
		while (j < MAPSIZE)
		{
			if (i == 0)
				d->map[i][j] = '1';
			else if (i == MAPSIZE - 1)
				d->map[i][j] = '1';
			else if (j == 0)
				d->map[i][j] = '1';
			else if (j == MAPSIZE - 1)
				d->map[i][j] = '1';
			else
				d->map[i][j] = '0';
			printf((j == MAPSIZE - 1 ? "%c\n": "%c"), (char)d->map[i][j]);
			j++;
		}
		i++;
	}
}

void	init_player(t_player *p)
{
	p->pos = (t_vec2f){5, 5};
	p->dir = (t_vec2f){0,1};
}

int		main(int ac, char **av)
{
	t_data		d;

	(void)ac;
	(void)av;
	init_map(&d);
	init_player(&d.p);
	init_mlx(&d);
	refresh_minimap(&d);
	mlx_loop(d.mlx);
}
