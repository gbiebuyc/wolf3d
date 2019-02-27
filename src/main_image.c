/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:52 by nallani           #+#    #+#             */
/*   Updated: 2019/02/27 05:16:00 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_map_coord(t_data *d, int i)
{
	if (d->map[i] == '0')
		return (0);
	if (!(d->map[i]))
		ft_putendl("problem with check_map");
	else
		return (d->map[i]);
	return (0);
}

int		change_mmap_into_color(int i)
{
	if (i == '1')
		return (0xFF00);
	return (0);
}

void	debug_draw_dir_and_plane(t_data *d)
{
	t_vec2f a = mul_vec2f(add_vec2f(d->pos, d->dir), SQUARE_W);
	draw_ray(&d->minimap, mul_vec2f(d->pos, SQUARE_W), a, 0xFFFFFF);
	t_vec2f b = add_vec2f(a, mul_vec2f(d->plane, SQUARE_W));
	draw_ray(&d->minimap, a, b, 0xFFFFFF);
}

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

void	find_intersection(t_data *d, t_vec2f ray_dir, int x)
{
	t_inter	c1; // nouvelle structure
	t_inter	c2;
	float	dist;

	c1 = find_intersection_ver(d, ray_dir, 0, (t_vec2f){0, 0}); // nouvelle structure
	c2 = find_intersection_hor(d, ray_dir, 0, (t_vec2f){0, 0});
	if ((c1.l < c2.l && c1.c != '0') || c2.c == '0') // Vertical intersection ray is shorter
	{
		draw_ray(&d->minimap, d->pos, c1.vec, 0xFF0000);
		dist = sqrt(c1.l);
	}
	else // Horizontal ray is shorter
	{
		draw_ray(&d->minimap, d->pos, c2.vec, 0xFF);
		dist = sqrt(c2.l);
		c1 = c2; // argument envoye a draw_column
	}
//	printf("ver: %f   hor: %f\n", c1.l, c2.l); // debug
//	printf("%c\n", c1.c); // debug

	draw_column(d, d->camera.h / dist /* sqrt(get_vec2f_length(d->dir))*/, x, c1.c); // remettre com si dir change (sqrt(1))
	// besoin de modifier le vecteur dir (dont delete me)
	// modifier calcul 2eme argument en mutipliant par cos(angle) pour enlever effet aquarium
}

void	refresh_image(t_data *d)
{
	/*
	t_vec2f		start;
	int			i;
	t_vec2		origin;

//	ft_memset(d->camera.pixels, 0, WIDTH * HEIGHT * 4);
	start = d->p.dir;
	actualize_dir(FOV / -2.0, &start);
	i = 0;
	origin = convert_vec2f(mul_vec2f(d->p.pos, SQUARE_W));
	while (i++ < 200)
	{
		draw_ray(d->minimap.img, origin, add_vec2(origin, convert_vec2f(mul_vec2f(start, SQUARE_W * 100))), 0xFFFFFF);
		actualize_dir(FOV / 199.0, &start);
		printf("ox:%d, oy:%d, dx:%d, dy:%d,    i:%d\n", origin.x, origin.y, add_vec2(origin, convert_vec2f(mul_vec2f(start, SQUARE_W * 100))).x, add_vec2(origin, convert_vec2f(mul_vec2f(start, SQUARE_W * 100))).y, i);
		printf("%f\n",  (float)((float)add_vec2(origin, convert_vec2f(mul_vec2f(start, SQUARE_W * 100))).x - (float)origin.x) / (float)((float)add_vec2(origin, convert_vec2f(mul_vec2f(start, SQUARE_W * 100))).y - (float)origin.y));
	}
	draw_ray(&d->minimap, (t_vec2f){1, 1}, (t_vec2f){7, 7}, 0xFFFFFF);
	draw_ray(&d->minimap, (t_vec2f){7, 1}, (t_vec2f){1, 7}, 0xFFFFFF);
	*/
	int		x;
	t_vec2f	ray_dir;

	x = 0;
	while (x < WIDTH)
	{
		// ray_dir = dir + plane * x / w
		ray_dir = add_vec2f(d->dir,
				mul_vec2f(d->plane, 2.0 * x / WIDTH - 1.0));
//		if (x == WIDTH / 2) // DEBUG LINE ONLY ONE RAY
		find_intersection(d, ray_dir, WIDTH - x); // width - x sinon s'affiche a l'envers (? car axe Y a l'envers ?)
		draw_ray(&d->minimap,
				d->pos,
				add_vec2f(d->pos, ray_dir), 0xFFFFFF);
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
