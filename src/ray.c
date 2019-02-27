/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:05 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/27 03:50:15 by nallani          ###   ########.fr       */
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

char	check_on_minimap_down(t_vec2f pos, t_data *d)
{
	t_vec2	truepos;

	truepos = convert_vec2f(pos);
	if (!(truepos.x < d->mapsize.x && truepos.y < d->mapsize.y && truepos.x > 0 && truepos.y > 0))
		return (-1);
		if (d->map[truepos.x + truepos.y * d->mapsize.y] != EMPTY_SQUARE)
		{
			return (d->map[truepos.x + truepos.y * d->mapsize.y]);	
		}
//	printf("check.x: %f check.y: %f\n",pos.x, pos.y);
	return (0);
}

char	check_on_minimap_up(t_vec2f pos, t_data *d)
{
	t_vec2	truepos;

	truepos = convert_vec2f(pos);
	if (!(truepos.x < d->mapsize.x && truepos.y < d->mapsize.y && truepos.x > 0 && truepos.y > 0))
		return (-1);
	truepos.y -=1; // super magic trick
		if (d->map[truepos.x + truepos.y * d->mapsize.y] != EMPTY_SQUARE)
		{
			return (d->map[truepos.x + truepos.y * d->mapsize.y]);	
		}
//	printf("check.x: %f check.y: %f\n",pos.x, pos.y);
	return (0);
}

char	check_on_minimap_left(t_vec2f pos, t_data *d)
{
	t_vec2	truepos;

	truepos = convert_vec2f(pos);
	if (!(truepos.x < d->mapsize.x && truepos.y < d->mapsize.y && truepos.x > 0 && truepos.y > 0))
		return (-1);
	truepos.x -=1; // super magic trick
		if (d->map[truepos.x + truepos.y * d->mapsize.y] != EMPTY_SQUARE)
		{
			return (d->map[truepos.x + truepos.y * d->mapsize.y]);	
		}
//	printf("check.x: %f check.y: %f\n",pos.x, pos.y);
	return (0);
}

char	check_on_minimap_right(t_vec2f pos, t_data *d)
{
	t_vec2	truepos;

	truepos = convert_vec2f(pos);
	if (!(truepos.x < d->mapsize.x && truepos.y < d->mapsize.y && truepos.x > 0 && truepos.y > 0))
		return (-1);
		if (d->map[truepos.x + truepos.y * d->mapsize.y] != EMPTY_SQUARE)
		{
			return (d->map[truepos.x + truepos.y * d->mapsize.y]);	
		}
//	printf("check.x: %f check.y: %f\n",pos.x, pos.y);
	return (0);
}

t_inter	find_intersection_hor(t_data *d, t_vec2f ray, int count, t_vec2f added_dist)
{
	t_vec2f	side_dist;
	t_vec2f	delta_dist;
	char	result;

	if (ray.y < 0)
		side_dist.y = (int)d->pos.y - d->pos.y;
	if (ray.y > 0)
		side_dist.y = (int)(d->pos.y + 1) - d->pos.y;
	if (ray.y == 0)
		return ((t_inter){10000, 0, added_dist}); // super length
	side_dist.x = side_dist.y * (ray.x / ray.y);
	delta_dist.x = ray.x / fabs(ray.y);
	delta_dist.y = ray.y > 0 ? 1 : -1;
	while (count++ < 100)
	{		
		if (ray.y > 0 && (result = check_on_minimap_down(add_vec2f(add_vec2f(d->pos, side_dist), added_dist), d)))
			break ;
		if (ray.y < 0 && (result = check_on_minimap_up(add_vec2f(add_vec2f(d->pos, side_dist), added_dist), d)))
			break ;
		added_dist = add_vec2f(added_dist, delta_dist);
	}
//	printf("%c pos.x: %f  pos.y:%f\n", result, add_vec2f(add_vec2f(d->pos, side_dist), added_dist).x, add_vec2f(add_vec2f(d->pos, side_dist), added_dist).y);
	if (result == -1)
		return ((t_inter){10000, 0, added_dist}); // super length
	return ((t_inter){get_vec2f_length(add_vec2f(added_dist, side_dist)), result, add_vec2f(add_vec2f(d->pos, side_dist), added_dist)});
}

t_inter	find_intersection_ver(t_data *d, t_vec2f ray, int count, t_vec2f added_dist)
{
	t_vec2f	side_dist;
	t_vec2f	delta_dist;
	char	result;

	if (ray.x < 0)
		side_dist.x = (int)d->pos.x - d->pos.x;
	if (ray.x > 0)
		side_dist.x = (int)(d->pos.x + 1) - d->pos.x;
	if (ray.x == 0)
		return ((t_inter){10000, 0, added_dist}); // super length
	side_dist.y = side_dist.x * (ray.y / ray.x);
	delta_dist.y = ray.y / fabs(ray.x);
	delta_dist.x = ray.x > 0 ? 1 : -1;
	while (count++ < 100)
	{		
		if (ray.x > 0 && (result = check_on_minimap_right(add_vec2f(add_vec2f(d->pos, side_dist), added_dist), d)))
			break ;
		if (ray.x < 0 && (result = check_on_minimap_left(add_vec2f(add_vec2f(d->pos, side_dist), added_dist), d)))
			break ;
		added_dist = add_vec2f(added_dist, delta_dist);
	}
//	printf("%c pos.x: %f  pos.y:%f\n", result, add_vec2f(add_vec2f(d->pos, side_dist), added_dist).x, add_vec2f(add_vec2f(d->pos, side_dist), added_dist).y);
	if (result == -1)
		return ((t_inter){10000, 0, added_dist}); // super length
	return ((t_inter){get_vec2f_length(add_vec2f(added_dist, side_dist)), result, add_vec2f(add_vec2f(d->pos, side_dist), added_dist)});
}
