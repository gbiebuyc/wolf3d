/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:52 by nallani           #+#    #+#             */
/*   Updated: 2019/03/04 00:30:24 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	get_asset(char c) // a voir avec find_colo_mini
{
	if (c == '1')
		return (0xFF00);
	if (c == '2')
		return (0xFF);
	if (c == '3')
		return (0xCC7700);
	printf("debug get_asset%c\n", c);
	return (0);
}

void	draw_column(t_data *d, int block_h, int x, t_inter inter)
{
	int		start;
	int		y;
	int		scaled_width;
	double	increment;
	double	real_y;

	// start = d->hooks.middle_screen - block_h / 2; // sorry pas le choix
	start = d->camera.h / 2 - block_h / 2;
	y = 0;
	scaled_width = inter.xtexture * d->textures[inter.c - '1'][inter.orientation].w;
	increment = (double)d->textures[inter.c - '1'][inter.orientation].h / (float)block_h;
	real_y = start < 0 ? -start * increment : 0;
	while (y < d->camera.h && block_h > 0)
	{
		if (y > start)
		{
			if (x >= 0 && y >= 0 && y < d->camera.h && x < d->camera.w)
			{
				d->camera.pixels[x + y * d->camera.w] =
					d->textures[inter.c - '1'][inter.orientation].pixels[scaled_width +
					(int)(real_y) * d->textures[inter.c - '1'][inter.orientation].w];
			}
			real_y += increment;
			if ((int)real_y >=
					d->textures[inter.c - '1'][inter.orientation].h)
				break;
			block_h--;
		}
		y++;
	}
}

uint32_t	getpixel(t_img *texture, double x, double y)
{
	return (texture->pixels[(int)(texture->w * x) +
			(int)(texture->h * y) * texture->w]);
}

void	draw_floor(t_data *d, int x, int block_h, t_inter inter, double angle)
{
	t_vec2f	ray;
	t_vec2f	pos_floor;
	t_vec2f	pos_sky;
	int		y;

	ray = sub_vec2f(inter.vec, d->pos);
	ray = mul_vec2f(ray, 1.0 / vec2f_length(ray));
	y = ft_max(block_h / 2, 1);
	while (y <= (d->camera.h / 2))
	{
		pos_floor = add_vec2f(d->pos, mul_vec2f(ray,
					1.0 / (((double)y / (d->camera.h / 2)) * cos(angle))));
		pos_sky = add_vec2f(mul_vec2f(d->pos, 0.3), mul_vec2f(ray,
					1.0 / (((double)y / (d->camera.h / 2)) * cos(angle))));
		pos_floor.x -= floor(pos_floor.x);
		pos_floor.y -= floor(pos_floor.y);
		pos_sky.x = pos_sky.x / 8 - floor(pos_sky.x / 8);
		pos_sky.y = pos_sky.y / 8 - floor(pos_sky.y / 8);
		putpixel(&d->camera, x, (d->camera.h / 2 + y),
				getpixel(&d->textures[0][1], pos_floor.x, pos_floor.y));
		putpixel(&d->camera, x, (d->camera.h / 2 - y),
				getpixel(&d->sky_texture, pos_sky.x, pos_sky.y));
		y++;
	}
}

void	find_intersection(t_args *args)
{
	args->inter[0] = find_intersection_ver(args->ray_dir, args->d);
	args->inter[1] = find_intersection_hor(args->ray_dir, args->d);
	args->dist = 0.0;
	if (args->inter[0].c != EMPTY_SQUARE && args->inter[0].l < args->inter[1].l) // Vertical intersection ray is shorter
	{
		draw_ray(&args->d->minimap, args->d->pos, args->inter[0].vec, 0xFF0000);
		args->dist = sqrt(args->inter[0].l);
	}
	else if (args->inter[1].c != EMPTY_SQUARE) // Horizontal ray is shorter
	{
		draw_ray(&args->d->minimap, args->d->pos, args->inter[1].vec, 0xFF);
		args->dist = sqrt(args->inter[1].l);
		args->inter[0] = args->inter[1]; // argument envoye a draw_column
	}
//	printf("ver: %f   hor: %f\n", c1.l, c2.l); // debug
//	printf("%c\n", c1.c); // debug

	args->dist *= cos(args->angle); // correction de la distortion
	if (args->inter[0].c != EMPTY_SQUARE)
		draw_column(args->d, args->d->camera.h / args->dist /* sqrt(get_vec2f_length(d->dir))*/, args->x, args->inter[0]); // remettre com si dir change (sqrt(1))
	draw_floor(args->d, args->x, args->d->camera.h / args->dist, args->inter[0], args->angle);
	// besoin de modifier le vecteur dir (dont delete me)
}

void	set_args(t_args	*args, t_data *d, t_vec2f ray_dir, int x)
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
		// ray_dir = dir + plane * x / w
		ray_dir = add_vec2f(d->dir, mul_vec2f(d->plane,
					2.0 * (coord.x  + coord.y)/ WIDTH - 1.0));
		set_args(&args[coord.y - 1], d, ray_dir, WIDTH - coord.x - coord.y);
		if (pthread_create(&id[coord.y - 1], NULL, (void *)&find_intersection, &args[coord.y - 1]))
			exit(EXIT_FAILURE);
		}
		coord.x += 4;
		pthread_join(id[0], NULL);
		pthread_join(id[1], NULL);
		pthread_join(id[2], NULL);
		pthread_join(id[3], NULL);
	}
}

void	reset_camera(t_data *d) // permet de reinitialiser l'image avec le sol et le ciel
{
	int		x;
	int		y;

	y = 0;
	while (y < d->hooks.middle_screen)
	{
		x = 0;
		while (x < d->camera.w)
		{
			d->camera.pixels[x + y * d->camera.w] = SKY_COLOR;
			x++;
		}
		y++;
	}
	while (y < d->camera.h)
	{
		x = 0;
		while (x < d->camera.w)
		{
			d->camera.pixels[x + y * d->camera.w] = GROUND_COLOR;
			x++;
		}
		y++;
	}
}

void	refresh_all(t_data *d)
{
	//reset_camera(d); // reset l'image de la camera // remplacé par textures sky et floor
	if (d->hooks.minimap)
	refresh_minimap(d);
	refresh_image(d);
	mlx_put_image_to_window(d->mlx, d->win, d->camera.mlximg, 0, 0);
	for (int i = 0; i < d->minimap.w * d->minimap.h; i++)
	{
		d->minimap.pixels[i] += 0x00000000;
	}
	if (d->hooks.minimap)
	mlx_put_image_to_window(d->mlx, d->win, d->minimap.mlximg, WIDTH - d->minimap.w, 0);
}
