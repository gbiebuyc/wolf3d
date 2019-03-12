/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:13:49 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/03/12 21:45:28 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_vec2	sub_vec2(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x - v2.x, v1.y - v2.y});
}

t_vec2f	sub_vec2f(t_vec2f v1, t_vec2f v2)
{
	return ((t_vec2f){v1.x - v2.x, v1.y - v2.y});
}

t_vec2f	add_vec2f(t_vec2f v1, t_vec2f v2)
{
	return ((t_vec2f){v1.x + v2.x, v1.y + v2.y});
}

void	actualize_dir(double diff, t_vec2f *dir)
{
	double	x;
	double	y;

	x = dir->x;
	y = dir->y;
	dir->x = x * cos(diff) - y * sin(diff);
	dir->y = x * sin(diff) + y * cos(diff);
}
