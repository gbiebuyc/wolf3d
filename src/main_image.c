/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:52 by nallani           #+#    #+#             */
/*   Updated: 2019/02/26 20:15:41 by gbiebuyc         ###   ########.fr       */
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
		draw_ray(&d->minimap,
				d->pos,
				add_vec2f(d->pos, ray_dir), 0xFFFFFF);
		x++;
	}
}

void	refresh_all(t_data *d)
{
	refresh_minimap(d);
	refresh_image(d);
	mlx_put_image_to_window(d->mlx, d->win, d->minimap.mlximg, WIDTH - d->minimap.w, 0);
}
