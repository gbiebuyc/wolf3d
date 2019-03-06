/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 02:02:29 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/06 20:08:01 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

uint32_t	rgb_add(uint32_t a, uint32_t b)
{
	return ((ft_min(0xff, ((a >> 16) & 0xff) + ((b >> 16) & 0xff)) << 16) |
			(ft_min(0xff, ((a >> 8) & 0xff) + ((b >> 8) & 0xff)) << 8) |
			(ft_min(0xff, ((a >> 0) & 0xff) + ((b >> 0) & 0xff)) << 0));
}

uint32_t	rgb_sub(uint32_t a, uint32_t b)
{
	return ((ft_max(0, (int)((a >> 16) & 0xff) - (int)((b >> 16) & 0xff)) << 16) |
			(ft_max(0, (int)((a >> 8) & 0xff) - (int)((b >> 8) & 0xff)) << 8) |
			(ft_max(0, (int)((a >> 0) & 0xff) - (int)((b >> 0) & 0xff)) << 0));
}

uint32_t	rgb_mul(uint32_t a, double factor)
{
	if (factor < 0)
		return (0);
	return ((ft_min(0xff, ((a >> 16) & 0xff) * factor) << 16) |
			(ft_min(0xff, ((a >> 8) & 0xff) * factor) << 8) |
			(ft_min(0xff, ((a >> 0) & 0xff) * factor) << 0));
}

extern inline uint32_t	calculate_fog(int y, int max_y, uint32_t fog_color, uint32_t p)
{
	if (5 * y > max_y)
		return (p);
		double factor = (double)(max_y - y * 5) / max_y;
		return (rgb_add(p, rgb_mul(rgb_sub(fog_color, p), factor)));
}
