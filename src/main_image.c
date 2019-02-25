/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:20:52 by nallani           #+#    #+#             */
/*   Updated: 2019/02/25 19:19:05 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_map_coord(t_data *data, int i)
{
	if (data->map[i] == '0')
		return (0);
	if (!(data->map[i]))
		ft_putendl("problem with check_map");
	else
		return (data->map[i]);
}

int		change_mmap_into_color(int i)
{
	if (i == '1')
		return (0xFF00);
}

void	refresh_image(t_data *d)
{
	t_vec2f		start;
	t_vec2f		dif;
	t_vec2f		end;

	ft_memset(data->camera.pixels, 0, WIDTH * HEIGHT * 4);
	start = d->pos.dir;
	actualize_dir(-0.25 * M_PI, start);
	end = d->pos.dir;
	actualize_dir(0.2 * M_PI, start);
	dif.x = end.x - start.x;
	dif.y = end.y - start.y;



	mlx_put_image_to_window(d->mlx, d->win, d->camera.img, 0, 0);
}

void	refresh_all(t_data *d)
{
	refresh_image(d);
	refresh_minimap(d);
}
