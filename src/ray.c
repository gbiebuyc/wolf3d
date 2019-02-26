/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:05 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/26 19:44:09 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define MAX_RAY_LENGTH 10.0

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

/* not finished
char	find_intersection(t_data *d, t_vec2f *ray)
{
	t_vec2	curr_square;
	t_vec2f	side_dist;
	t_vec2f	delta_dist;

	curr_square = (t_vec2){(int)d->pos.x, (int)d->pos.y};
	if (ray->x > 0)
	{

	}
	while (42)
	{
		if (ray.x * ray.x + ray.y * ray.y >= MAX_RAY_LENGTH * MAX_RAY_LENGTH)
			return (EMPTY_SQUARE);
		else if (d->map[curr_square.x + curr_square.y * d->mapsize.y] != EMPTY_SQUARE)
			return (d->map[curr_square.x + curr_square.y * d->mapsize.y]);
	}
}
*/
