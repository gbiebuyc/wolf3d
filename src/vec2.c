/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:13:49 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/03 05:44:05 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_vec2	sub_vec2(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x - v2.x, v1.y - v2.y});
}

t_vec2	add_vec2(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x + v2.x, v1.y + v2.y});
}

t_vec2 mul_vec2(t_vec2 v, int mult)
{
	return ((t_vec2){v.x * mult, v.y * mult});	
}

t_vec2f	sub_vec2f(t_vec2f v1, t_vec2f v2)
{
	return ((t_vec2f){v1.x - v2.x, v1.y - v2.y});
}

t_vec2f	add_vec2f(t_vec2f v1, t_vec2f v2)
{
	return ((t_vec2f){v1.x + v2.x, v1.y + v2.y});
}

t_vec2f	mul_vec2f(t_vec2f v, double scalar)
{
	return ((t_vec2f){v.x * scalar, v.y * scalar});
}

t_vec2 convert_vec2f(t_vec2f v)
{
	return ((t_vec2){(int)v.x, (int)v.y});
}

float	get_vec2f_length(t_vec2f v)
{
	return (v.x * v.x + v.y * v.y); // skip sqrt pour perf
}

double	vec2f_length(t_vec2f v) // vraie longueur avec sqrt
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double	get_vec2f_angle(t_vec2f v1, t_vec2f v2)
{
	return (atan2(v1.x * v2.y - v1.y * v2.x, v1.x * v2.x + v1.y * v2.y));
}
