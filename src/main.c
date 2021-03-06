/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:00:33 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/16 22:34:23 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_mlx(t_data *d, int junk)
{
	d->camera.w = WIDTH;
	d->camera.h = HEIGHT;
	d->minimap.w = MINIMAPSIZE * SQUARE_W;
	d->minimap.h = MINIMAPSIZE * SQUARE_W;
	if (!(d->mlx = mlx_init()))
		err_exit(d, 1, "mlx_init has failed", EXIT_FAILURE);
	if (!(d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "wolf3d")))
		err_exit(d, 2, "mlx_new_window has failed", EXIT_FAILURE);
	if (!(d->camera.mlximg = mlx_new_image(d->mlx, d->camera.w, d->camera.h)))
		err_exit(d, 3, "mlx_new_image has failed", EXIT_FAILURE);
	if (!(d->minimap.mlximg =
				mlx_new_image(d->mlx, d->minimap.w, d->minimap.h)))
		err_exit(d, 4, "mlx_new_image has failed", EXIT_FAILURE);
	d->camera.pixels = (uint32_t*)mlx_get_data_addr(
			d->camera.mlximg, &junk, &junk, &junk);
	d->minimap.pixels = (uint32_t*)mlx_get_data_addr(
			d->minimap.mlximg, &junk, &junk, &junk);
	mlx_hook(d->win, 2, 1L << 0, key_press, d);
	mlx_hook(d->win, 3, 1L << 1, key_release, d);
	mlx_hook(d->win, 6, 1L << 6, mouse_move, d);
	mlx_hook(d->win, 17, 1L << 17, proper_exit, d);
	mlx_loop_hook(d->mlx, &refresh_loop, d);
}

void	init_player(t_data *d)
{
	d->pos = (t_vec2f){3.5, 3.5};
	d->dir = (t_vec2f){0, 1};
	d->plane = (t_vec2f){0.66, 0};
	d->hooks.dir = 0;
	d->hooks.strafe_dir = 0;
	d->hooks.hor_rot = 0;
	d->hooks.middle_screen = HEIGHT / 2;
	d->hooks.run = 0;
	d->hooks.scroll.x = 0;
	d->hooks.scroll.y = 0;
	d->score = 0;
	d->ignore_mouse = 0;
}

void	parse_argv(char **argv, t_data *d)
{
	while (*++argv)
	{
		while (**argv)
		{
			if (**argv >= '0' && **argv <= '9')
				d->map_path[ft_strlen(d->map_path) - 1] = **argv;
			else if (**argv == 'r')
				d->gamestate = RACE;
			else
			{
				ft_putstr_fd("usage: wolf3d [map nbr] [r]\n"
						"r = race mode\n", STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
			(*argv)++;
		}
	}
}

int		main(int ac, char **av)
{
	t_data		d;

	d = (t_data){.map_path = MAP_PATH, .gamestate = PLAY, .hooks.minimap = 1};
	if (ac >= 2)
		parse_argv(av, &d);
	init_map(&d, "", 0, 0);
	init_player(&d);
	init_mlx(&d, 0);
	if (d.gamestate == PLAY)
		mlx_mouse_hide();
	load_textures(&d);
	refresh_all(&d);
	mlx_loop(d.mlx);
}
