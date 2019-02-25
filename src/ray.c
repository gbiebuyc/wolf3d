/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:05 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/25 19:05:15 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_ray(t_img *img, t_vec2 v1, t_vec2 v2, uint32_t color)
{
	t_vec2	delta;
	int		steps;
	t_vec2f	increment;
	t_vec2f	pos;

	delta.x = v2.x - v1.x;
	delta.y = v2.y - v1.y;
	steps = (abs(delta.x) > abs(delta.y)) ? abs(delta.x) : abs(delta.y);
	increment.x = delta.x / (double)steps;
	increment.y = delta.y / (double)steps;
	pos = (t_vec2f){v1.x, v1.y};
	while (steps--)
	{
		putpixel(img, pos.x, pos.y, color);
		pos = add_vec2f(pos, increment);
	}
}
