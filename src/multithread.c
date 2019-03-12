/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:07:49 by nallani           #+#    #+#             */
/*   Updated: 2019/03/12 23:20:48 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	find_intersection(t_args *args)
{
	args->inter[0] = find_intersection_ver(args->ray_dir, args->d);
	args->inter[1] = find_intersection_hor(args->ray_dir, args->d);
	args->dist = 0.0;
	if (args->inter[0].c != EMPTY_SQUARE && args->inter[0].l <
			args->inter[1].l)
	{
		if (args->d->hooks.minimap)
			draw_ray(args->d, args->inter[0].vec, 0xFF0000); //supp ?
		args->dist = sqrt(args->inter[0].l);
	}
	else if (args->inter[1].c != EMPTY_SQUARE)
	{
		if (args->d->hooks.minimap)
			draw_ray(args->d, args->inter[1].vec, 0xFF); //supp ?
		args->dist = sqrt(args->inter[1].l);
		args->inter[0] = args->inter[1];
	}
	else
		args->inter[0] = args->inter[(args->d->dir.x == 0 ? 1 : 0)];
	args->dist *= cos(args->angle);
	if (args->inter[0].c != EMPTY_SQUARE)
		draw_column(args->d, args->d->camera.h / args->dist, args->x,
				args->inter[0]);
	draw_sky_and_floor(args->d, *args, args->d->camera.h / args->dist);
}

void	set_args(t_args *args, t_data *d, t_vec2f ray_dir, int x)
{
	args->d = d;
	args->ray_dir = ray_dir;
	args->x = x;
	args->angle = get_vec2f_angle(d->dir, ray_dir);
}

void	refresh_image(t_data *d)
{
	t_vec2		coord;
	t_vec2f		ray_dir;
	pthread_t	id[4];
	t_args		args[4];

	coord.x = 0;
	while (coord.x < WIDTH && !(coord.y = 0))
	{
		while (++coord.y < 5 && (coord.x + coord.y <= WIDTH))
		{
			ray_dir = add_vec2f(d->dir, mul_vec2f(d->plane,
						2.0 * (coord.x + coord.y) / WIDTH - 1.0));
			set_args(&args[coord.y - 1], d, ray_dir, WIDTH - coord.x - coord.y);
			if (pthread_create(&id[coord.y - 1], NULL,
						(void *)&find_intersection,
						&args[coord.y - 1]))
				err_exit(d, 10, strerror(errno), EXIT_FAILURE);
		}
		coord.x += 4;
		pthread_join(id[0], NULL);
		pthread_join(id[1], NULL);
		pthread_join(id[2], NULL);
		pthread_join(id[3], NULL);
	}
}

void	refresh_all(t_data *d)
{
	int i;

	if (d->hooks.minimap)
		refresh_minimap(d);
	refresh_image(d);
	mlx_put_image_to_window(d->mlx, d->win, d->camera.mlximg, 0, 0);
	i = -1;
	while (++i < d->minimap.w * d->minimap.h)
		d->minimap.pixels[i] += 0x80 << 24;
	if (d->hooks.minimap)
		mlx_put_image_to_window(d->mlx, d->win, d->minimap.mlximg, WIDTH -
				d->minimap.w, 0);
}
