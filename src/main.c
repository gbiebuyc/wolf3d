/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:00:33 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/27 04:34:07 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_mlx(t_data *d)
{
	int		junk;

	d->camera.w = WIDTH;
	d->camera.h = HEIGHT;
	d->minimap.w = d->mapsize.x * SQUARE_W;
	d->minimap.h = d->mapsize.y * SQUARE_W;
	if (!(d->mlx = mlx_init()) ||
			!(d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "wolf3d")) ||
			!(d->camera.mlximg = mlx_new_image(
					d->mlx, d->camera.w, d->camera.h)) ||
			!(d->minimap.mlximg = mlx_new_image(
					d->mlx, d->minimap.w, d->minimap.h)))
	{
		ft_putstr_fd("rip mlx\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	d->camera.pixels = (uint32_t*)mlx_get_data_addr(
			d->camera.mlximg, &junk, &junk, &junk);
	d->minimap.pixels = (uint32_t*)mlx_get_data_addr(
			d->minimap.mlximg, &junk, &junk, &junk);
	mlx_hook(d->win, 2, 1L << 0, key_press, d);
	mlx_hook(d->win, 4, 1L << 2, mouse_press, d);
	mlx_hook(d->win, 5, 1L << 3, mouse_release, d);
	mlx_hook(d->win, 6, 1L << 6, mouse_move, d);
	mlx_hook(d->win, 17, 1L << 17, destroy_event, d);
}

void	init_map(t_data *d)
{
	static char *m =
		"11111111"
		"1 1    1"
		"1    1 1"
		"1    1 1"
		"1      1"
		"1   3211"
		"11     1"
		"11111111";
	d->map = m;
	d->mapsize = (t_vec2){8, 8};
}

void	init_player(t_data *d)
{
	d->pos = (t_vec2f){3.5, 3.5};
	d->dir = (t_vec2f){0,1};
	d->plane = (t_vec2f){0.66,0};
}

int		main(int ac, char **av)
{
	t_data		d;

	(void)ac;
	(void)av;
	init_map(&d);
	init_player(&d);
	init_mlx(&d);
	refresh_all(&d);
	mlx_loop(d.mlx);
}
