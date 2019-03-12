/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 08:50:40 by nallani           #+#    #+#             */
/*   Updated: 2019/03/12 21:53:18 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

short	get_max_frames(short nb)
{
	if (nb == 1)
		return (PIKA_FRAMES);
	if (nb == 0)
		return (RYU_FRAMES);
	return (0);
}

int		proper_exit(t_data *d)
{
	int		i;
	t_img	*tmp;
	t_exit_count	count;

	i = 0;
	while (i <= WEST)
	{
		mlx_destroy_image(d->mlx, d->textures[0][i].mlximg);
		i++;
	}
	count.max_anim = MAX_ANIM;
	while (count.max_anim-- > 0)
	{
		count.max_frames[count.max_anim] = get_max_frames(count.max_anim);
		while (count.max_frames[count.max_anim]--)
		{
			tmp = d->anim[count.max_anim]->next;
			mlx_destroy_image(d->mlx, d->anim[count.max_anim]->mlximg);
			d->anim[count.max_anim]->next = NULL;
			free(d->anim[count.max_anim]);
			d->anim[count.max_anim] = tmp;
		}
	}
	mlx_destroy_image(d->mlx, d->sky_texture.mlximg);
	mlx_destroy_image(d->mlx, d->minimap.mlximg);
	mlx_destroy_image(d->mlx, d->camera.mlximg);
	free(d->map);
	mlx_destroy_window(d->mlx, d->win);
	free(d->mlx);
	exit(0);
	return (421);
}

void	err_exit(t_data *d, int mod, char *msg, int exit_code) // UNTESTED
{
	ft_putendl_fd(msg, STDERR_FILENO);
	if (mod > 9)
		mlx_destroy_image(d->mlx, d->sky_texture.mlximg);
	if (mod > 8)
		mlx_destroy_image(d->mlx, d->textures[0][WEST].mlximg);
	if (mod > 7)
		mlx_destroy_image(d->mlx, d->textures[0][EAST].mlximg);
	if (mod > 6)
		mlx_destroy_image(d->mlx, d->textures[0][SOUTH].mlximg);
	if (mod > 5)
		mlx_destroy_image(d->mlx, d->textures[0][NORTH].mlximg);
	if (mod > 4)
		mlx_destroy_image(d->mlx, d->minimap.mlximg);
	if (mod > 3)
		mlx_destroy_image(d->mlx, d->camera.mlximg);
	if (mod > 2)
		mlx_destroy_window(d->mlx, d->win);
	if (mod > 1)
		free(d->mlx);
	if (mod > 0)
		free(d->map);
	exit(exit_code);
}
