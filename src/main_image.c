/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:52 by nallani           #+#    #+#             */
/*   Updated: 2019/02/28 06:16:52 by gbiebuyc         ###   ########.fr       */
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

void	draw_column(t_data *d, int block_h, int x, char c)
{
	int		start;
	int		y;

	start = d->camera.h / 2 - block_h / 2;
	y = 0;
	while (y < d->camera.h)
	{
		if (y > start && block_h)
		{
			if (x > 0 && y > 0 && y < d->camera.h && x < d->camera.w)
				d->camera.pixels[x + y * d->camera.w] = get_asset(c);
			block_h--;
		}
		y++;
	}
}

void	find_intersection(t_data *d, t_vec2f ray_dir, int x, double angle)
{
	t_inter	c1; // nouvelle structure
	t_inter	c2;
	float	dist;

	c1 = find_intersection_ver(ray_dir, d);
	c2 = find_intersection_hor(ray_dir, d);
	if (c1.c != EMPTY_SQUARE && c1.l < c2.l) // Vertical intersection ray is shorter
	{
		draw_ray(&d->minimap, d->pos, c1.vec, 0xFF0000);
		dist = sqrt(c1.l);
	}
	else if (c2.c != EMPTY_SQUARE) // Horizontal ray is shorter
	{
		draw_ray(&d->minimap, d->pos, c2.vec, 0xFF);
		dist = sqrt(c2.l);
		c1 = c2; // argument envoye a draw_column
	}
//	printf("ver: %f   hor: %f\n", c1.l, c2.l); // debug
//	printf("%c\n", c1.c); // debug

	dist *= cos(angle); // correction de la distortion
	if (c1.c != EMPTY_SQUARE)
		draw_column(d, d->camera.h / dist /* sqrt(get_vec2f_length(d->dir))*/, x, c1.c); // remettre com si dir change (sqrt(1))
	// besoin de modifier le vecteur dir (dont delete me)
	// modifier calcul 2eme argument en mutipliant par cos(angle) pour enlever effet aquarium
}

void	refresh_image(t_data *d)
{
	int		x;
	t_vec2f	ray_dir;

	x = 0;
	while (x < WIDTH)
	{
		// ray_dir = dir + plane * x / w
		ray_dir = add_vec2f(d->dir,
				mul_vec2f(d->plane, 2.0 * x / WIDTH - 1.0));
//		if (x == WIDTH / 2) // DEBUG LINE ONLY ONE RAY
		find_intersection(d, ray_dir, WIDTH - x, get_vec2f_angle(d->dir, ray_dir)); // width - x sinon s'affiche a l'envers (? car axe Y a l'envers ?)
		x++;
	}
}

void	reset_camera(t_data *d) // permet de reinitialiser l'image avec le sol et le ciel
{
	int		x;
	int		y;

	y = 0;
	while (y < d->camera.h / 2)
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
	reset_camera(d); // reset l'image de la camera
	refresh_minimap(d);
	refresh_image(d);
	mlx_put_image_to_window(d->mlx, d->win, d->camera.mlximg, 0, 0);
	mlx_put_image_to_window(d->mlx, d->win, d->minimap.mlximg, WIDTH - d->minimap.w, 0);
}
