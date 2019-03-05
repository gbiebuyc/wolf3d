/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:00:33 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/05 19:14:13 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_mlx(t_data *d)
{
	int		junk;

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
	if (!(d->minimap.mlximg = mlx_new_image(d->mlx, d->minimap.w, d->minimap.h)))
		err_exit(d, 4, "mlx_new_image has failed", EXIT_FAILURE);
	d->camera.pixels = (uint32_t*)mlx_get_data_addr(
			d->camera.mlximg, &junk, &junk, &junk);
	d->minimap.pixels = (uint32_t*)mlx_get_data_addr(
			d->minimap.mlximg, &junk, &junk, &junk);
	mlx_hook(d->win, 2, 1L << 0, key_press, d);
	mlx_hook(d->win, 3, 1L << 1, key_release, d);
	mlx_hook(d->win, 4, 1L << 2, mouse_press, d);
	mlx_hook(d->win, 5, 1L << 3, mouse_release, d);
	mlx_hook(d->win, 6, 1L << 6, mouse_move, d);
	mlx_hook(d->win, 17, 1L << 17, proper_exit, d);
	mlx_loop_hook(d->mlx, &refresh_loop, d);
}

void	init_player(t_data *d)
{
	d->pos = (t_vec2f){3.5, 3.5};
	d->dir = (t_vec2f){0,1};
	d->plane = (t_vec2f){0.66,0};
	d->hooks.dir = 0;
	d->hooks.minimap = 1;
	d->hooks.strafe_dir = 0;
	d->hooks.middle_screen = HEIGHT / 2;
	d->hooks.run = 0;
	d->hooks.scroll.x = 0;
	d->hooks.scroll.y = 0;
}

void	modify_img(uint32_t *colo)
{
	int	red;
	int	green;
	int	blue;

	red = *colo >> 16 & 0xFF;
	green = *colo >> 8 & 0xFF;
	blue = *colo & 0xFF;
	*colo = ((red / 2) << 16 | (green / 2) << 8 | (blue / 2));
}

void	load_textures(t_data *d)
{
	int	junk;
	int superjunk;
	char *super_sky[4] = {"textures/Surprise.xpm", "textures/Surprise1.xpm",
		"textures/Surprise2.xpm", "textures/Surprise3.xpm"};

	//srand(time(NULL));
	//superjunk = rand(); // CHEAT
	//superjunk %= 4;
	superjunk = ((int)&d->mlx / 100) % 4; // random à partir d'une addr, à voir...
	d->fog_color = (int[4]){0x433881, 0xe4b8dd, 0xffffff, 0x216c73}[superjunk];
	if (!(d->textures[0][NORTH].mlximg =
				mlx_xpm_file_to_image(d->mlx, "./textures/north.xpm",
					&d->textures[0][NORTH].w, &d->textures[0][NORTH].h)))
	err_exit(d, 5, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);	
	printf("heyy\n");
	if (!(d->textures[0][SOUTH].mlximg = 
				mlx_xpm_file_to_image(d->mlx, "./textures/south.xpm",
					&d->textures[0][SOUTH].w, &d->textures[0][SOUTH].h)))
	err_exit(d, 6, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);	
	if (!(d->textures[0][EAST].mlximg =
				mlx_xpm_file_to_image(d->mlx, "./textures/east.xpm",
					&d->textures[0][EAST].w, &d->textures[0][EAST].h)))
	err_exit(d, 7, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);	
	if (!(d->textures[0][WEST].mlximg =
				mlx_xpm_file_to_image(d->mlx, "./textures/west.xpm",
					&d->textures[0][WEST].w, &d->textures[0][WEST].h)))
	err_exit(d, 8, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);
	if (!(d->sky_texture.mlximg = mlx_xpm_file_to_image(d->mlx,
					super_sky[superjunk], &d->sky_texture.w, &d->sky_texture.h)))
	err_exit(d, 9, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);
	d->textures[0][NORTH].pixels = (uint32_t*)mlx_get_data_addr(
			d->textures[0][NORTH].mlximg, &junk, &junk, &junk);
	d->textures[0][SOUTH].pixels = (uint32_t*)mlx_get_data_addr(
			d->textures[0][SOUTH].mlximg, &junk, &junk, &junk);
	d->textures[0][EAST].pixels = (uint32_t*)mlx_get_data_addr(
			d->textures[0][EAST].mlximg, &junk, &junk, &junk);
	d->textures[0][WEST].pixels = (uint32_t*)mlx_get_data_addr(
			d->textures[0][WEST].mlximg, &junk, &junk, &junk);
	d->sky_texture.pixels = (uint32_t*)mlx_get_data_addr(
			d->sky_texture.mlximg, &junk, &junk, &junk);
	if (superjunk != 2)
	for (int i = 0; i < d->textures[0][NORTH].w; i++)
	for (int j = 0; j < d->textures[0][NORTH].h; j++)
	{
	modify_img(&d->textures[0][NORTH].pixels[i + j * d->textures[0][NORTH].w]);
	modify_img(&d->textures[0][WEST].pixels[i + j * d->textures[0][WEST].w]);
	modify_img(&d->textures[0][EAST].pixels[i + j * d->textures[0][EAST].w]);
	modify_img(&d->textures[0][SOUTH].pixels[i + j * d->textures[0][SOUTH].w]);
	}
}

int		main(int ac, char **av)
{
	t_data		d;

	(void)ac;
	(void)av;
	init_map(&d, "", 0, 0);
	printf("%s\n", d.map);
	init_player(&d);
	init_mlx(&d);
	load_textures(&d);
//	refresh_all(&d);
	mlx_loop(d.mlx);
}
