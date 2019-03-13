/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 08:50:40 by nallani           #+#    #+#             */
/*   Updated: 2019/03/13 18:46:40 by nallani          ###   ########.fr       */
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

void	free_textures(t_img *img, short nb_of_frames, void *mlx)
{
	t_img	*tmp;

	while (nb_of_frames-- > 0)
	{
		tmp = img->next;
		mlx_destroy_image(mlx, img->mlximg);
		free(img);
		img = NULL;
		img = tmp;
	}
}

int		proper_exit(t_data *d)
{
	int		i;
	short	count;

	i = 0;
	while (i <= WEST)
	{
		mlx_destroy_image(d->mlx, d->textures[0][i].mlximg);
		i++;
	}
	count = MAX_ANIM;
	while (count-- > 0)
		free_textures(d->anim[count], get_max_frames(count), d->mlx);
	mlx_destroy_image(d->mlx, d->sky_texture.mlximg);
	mlx_destroy_image(d->mlx, d->minimap.mlximg);
	mlx_destroy_image(d->mlx, d->camera.mlximg);
	free(d->map);
	mlx_destroy_window(d->mlx, d->win);
	free(d->mlx);
	exit(0);
	return (421);
}

void	err_exit(t_data *d, int mod, char *msg, int exit_code)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	if (mod > 10)
		free_textures(d->anim[0], get_max_frames(0), d->mlx);
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
