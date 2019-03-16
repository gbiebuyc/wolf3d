/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 08:50:40 by nallani           #+#    #+#             */
/*   Updated: 2019/03/16 03:53:39 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_textures(t_img *img, void *mlx)
{
	t_img	*tmp;
	t_img	*cmp;

	cmp = img;
	img = img->next;
	while (cmp != img)
	{
		tmp = img->next;
		mlx_destroy_image(mlx, img->mlximg);
		free(img);
		img->next = NULL;
		img = tmp;
	}
	mlx_destroy_image(mlx, cmp->mlximg);
	free(cmp);
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
		free_textures(d->anim[count], d->mlx);
	mlx_destroy_image(d->mlx, d->sky_texture.mlximg);
	mlx_destroy_image(d->mlx, d->minimap.mlximg);
	mlx_destroy_image(d->mlx, d->camera.mlximg);
	if (d->mapsize.x)
		free(d->map);
	mlx_destroy_window(d->mlx, d->win);
	free(d->mlx); // T'as vu où qu'il fallait free l'id de connection de la mlx?
	free(d->framebuf2);
	exit(0);
	return (421);
}

void	err_exit_2(t_data *d, int mod)
{
	if (mod > 11)
		free_textures(d->anim[1], d->mlx);
	if (mod > 12)
		free_textures(d->anim[2], d->mlx);
}

void	err_exit(t_data *d, int mod, char *msg, int exit_code)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	err_exit_2(d, mod);
	if (mod > 10)
		free_textures(d->anim[0], d->mlx);
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
	if (mod > 0 && d->mapsize.x)
		free(d->map);
	exit(exit_code);
}
