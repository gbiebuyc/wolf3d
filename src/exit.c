/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 08:50:40 by nallani           #+#    #+#             */
/*   Updated: 2019/03/03 09:21:56 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	proper_exit(t_data *d)
{
	int	i;

	i = 0;
	while (i <= WEST)
	{
	mlx_destroy_image(d->mlx, d->textures[0][i].mlximg);
	i++;
	}
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
	if (mod > 8) // ???
	mlx_destroy_image(d->mlx, d->textures[0][WEST].mlximg); // ???
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
