/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:52 by nallani           #+#    #+#             */
/*   Updated: 2019/03/12 23:17:01 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_column(t_data *d, int block_h, int x, t_inter inter)
{
	t_var	a;

	a.start = d->hooks.middle_screen - block_h / 2;
	a.y = -1;
	a.scaled_width = inter.xtexture * d->textures[inter.c -
		'1'][inter.orientation].w;
	a.increment = (double)d->textures[inter.c - '1'][inter.orientation].h
		/ (float)block_h;
	a.real_y = a.start < 0 ? -a.start * a.increment : 0;
	while (++a.y < d->camera.h && block_h > 0)
		if (a.y > a.start)
		{
			if (x >= 0 && a.y >= 0 && a.y < d->camera.h && x < d->camera.w)
				d->camera.pixels[x + a.y * d->camera.w] =
					calculate_fog(d->hooks.middle_screen - a.start, d->camera.h
							/ 2, d->fog_color, d->textures[inter.c - '1']
							[inter.orientation].pixels[a.scaled_width +
							(int)(a.real_y) * d->textures[inter.c - '1']
							[inter.orientation].w]);
			a.real_y += a.increment;
			if ((int)a.real_y >=
					d->textures[inter.c - '1'][inter.orientation].h)
				break ;
			block_h--;
		}
}

uint32_t	getpixel(t_img *texture, double x, double y)
{
	return (texture->pixels[(int)(texture->w * x) +
			(int)(texture->h * y) * texture->w]);
}

void		draw_floor(t_data *d, t_args inf, int block_h, t_vec2f ray)
{
	int		y;
	t_vec2f	pos_floor;

	y = ft_max(block_h / 2, 1);
	while (y + d->hooks.middle_screen <= d->camera.h)
	{
		pos_floor = add_vec2f(d->pos, mul_vec2f(ray,
					1.0 / (((double)y / (d->camera.h / 2)) * cos(inf.angle))));
		pos_floor.x -= floor(pos_floor.x);
		pos_floor.y -= floor(pos_floor.y);
		putpixel(&d->camera, inf.x, (d->hooks.middle_screen - 1 + y),
				calculate_fog(y, d->camera.h / 2, d->fog_color,
					getpixel(&d->textures[0][1], pos_floor.x, pos_floor.y)));
		y++;
	}
}

void		draw_sky_and_floor(t_data *d, t_args inf, int block_h)
{
	t_vec2f	ray;
	t_vec2f	pos_sky;
	int		y;

	ray = sub_vec2f(inf.inter[0].vec, d->pos);
	ray = mul_vec2f(ray, 1.0 / vec2f_length(ray));
	y = ft_max(block_h / 2, 1);
	while (y <= (d->hooks.middle_screen))
	{
		pos_sky = add_vec2f(mul_vec2f(d->pos, 0.2), mul_vec2f(ray,
					1.0 / (((double)y / (d->camera.h / 2)) * cos(inf.angle))));
		pos_sky.x = pos_sky.x - floor(pos_sky.x) + d->hooks.scroll.x;
		pos_sky.y = pos_sky.y - floor(pos_sky.y) + d->hooks.scroll.y;
		pos_sky.x -= ((int)pos_sky.x == 1 ? 1 : 0);
		pos_sky.y -= ((int)pos_sky.y == 1 ? 1 : 0);
		if ((int)(pos_sky.y * d->sky_texture.h) * d->sky_texture.w
				+ (int)(pos_sky.x * d->sky_texture.w) > d->sky_texture.w *
				d->sky_texture.h)
			pos_sky.y = 0;
		putpixel(&d->camera, inf.x, (d->hooks.middle_screen - y),
				calculate_fog(y, d->camera.h / 2, d->fog_color,
					getpixel(&d->sky_texture, pos_sky.x, pos_sky.y)));
		y++;
	}
	draw_floor(d, inf, block_h, ray);
}
