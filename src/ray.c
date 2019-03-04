/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:05 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/04 10:37:02 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_ray(t_img *img, t_vec2f v1, t_vec2f v2, uint32_t color)
{
	t_vec2	delta;
	int		steps;
	t_vec2f	increment;

	v1 = mul_vec2f(v1, SQUARE_W);
	v2 = mul_vec2f(v2, SQUARE_W);
	delta.x = v2.x - v1.x;
	delta.y = v2.y - v1.y;
	steps = (abs(delta.x) > abs(delta.y)) ? abs(delta.x) : abs(delta.y);
	increment.x = delta.x / (double)steps;
	increment.y = delta.y / (double)steps;
	while (steps--)
	{
		putpixel(img, (int)v1.x, (int)v1.y, color);
		v1 = add_vec2f(v1, increment);
	}
}

char	get_map_char(int x, int y, t_data *d)
{
	if (!(x >= 0 && y >= 0 && x < d->mapsize.x && y < d->mapsize.y))
		return (EMPTY_SQUARE);
	return (d->map[x + y * d->mapsize.x]);
}

t_inter	find_intersection_hor(t_vec2f ray, t_data *d)
{
	t_vec2f	hit;
	t_vec2f	delta;
	char	c;
	int		i;

	if (ray.y < 0)
		hit.y = floor(d->pos.y); // floor() pour éviter rounding bug dans négatif
	else
		hit.y = ceil(d->pos.y);
	hit.x = d->pos.x + (hit.y - d->pos.y) * ray.x / ray.y;
	delta.x = ray.x / fabs(ray.y);
	delta.y = ray.y > 0 ? 1 : -1;
	i = 0;
	while (i++ < 100)
	{
		if ((c = get_map_char(floor(hit.x), floor(ray.y > 0 ?
							hit.y : hit.y - 1), d)) != EMPTY_SQUARE)
			break;
		hit = add_vec2f(hit, delta);
	}
	return ((t_inter){get_vec2f_length(sub_vec2f(hit, d->pos)), c, hit,
			(ray.y > 0) ? NORTH : SOUTH, hit.x - floor(hit.x)});
}

t_inter	find_intersection_ver(t_vec2f ray, t_data *d)
{
	t_vec2f	hit;
	t_vec2f	delta;
	char	c;
	int		i;

	if (ray.x < 0)
		hit.x = floor(d->pos.x);
	else
		hit.x = ceil(d->pos.x);
	hit.y = d->pos.y + (hit.x - d->pos.x) * ray.y / ray.x;
	delta.x = ray.x > 0 ? 1 : -1;
	delta.y = ray.y / fabs(ray.x);
	i = 0;
	while (i++ < 100)
	{
		if ((c = get_map_char(floor(ray.x > 0 ? hit.x : hit.x - 1),
						floor(hit.y), d)) != EMPTY_SQUARE)
			break;
		hit = add_vec2f(hit, delta);
	}
	return ((t_inter){get_vec2f_length(sub_vec2f(hit, d->pos)), c, hit,
			(ray.x > 0) ? WEST : EAST, hit.y - floor(hit.y)});
}
