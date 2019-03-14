/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:34:51 by nallani           #+#    #+#             */
/*   Updated: 2019/03/14 19:22:37 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	modify_img(uint32_t *colo)
{
	int	red;
	int	green;
	int	blue;

	red = *colo >> 16 & 0xFF;
	green = *colo >> 8 & 0xFF;
	blue = *colo & 0xFF;
	*colo = ((red / 2) << 16 | (green / 2) << 8 | (blue / 2));
}

void	random_map(t_data *d, short random)
{
	short	i;
	short	j;

	i = -1;
	if (random != 2)
		while (++i < d->textures[0][NORTH].w)
		{
			j = -1;
			while (++j < d->textures[0][NORTH].h)
			{
				modify_img(&d->textures[0][NORTH].pixels[i + j
						* d->textures[0][NORTH].w]);
				modify_img(&d->textures[0][WEST].pixels[i + j
						* d->textures[0][WEST].w]);
				modify_img(&d->textures[0][EAST].pixels[i + j
						* d->textures[0][EAST].w]);
				modify_img(&d->textures[0][SOUTH].pixels[i + j
						* d->textures[0][SOUTH].w]);
			}
		}
}

void	load_textures_2(t_data *d, short random)
{
	int		junk;

	d->textures[0][NORTH].pixels = (uint32_t*)mlx_get_data_addr(
			d->textures[0][NORTH].mlximg, &junk, &junk, &junk);
	d->textures[0][SOUTH].pixels = (uint32_t*)mlx_get_data_addr(
			d->textures[0][SOUTH].mlximg, &junk, &junk, &junk);
	d->textures[0][EAST].pixels = (uint32_t*)mlx_get_data_addr(
			d->textures[0][EAST].mlximg, &junk, &junk, &junk);
	d->textures[0][WEST].pixels = (uint32_t*)mlx_get_data_addr(
			d->textures[0][WEST].mlximg, &junk, &junk, &junk);
	d->sky_texture.pixels = (uint32_t*)mlx_get_data_addr(
			d->sky_texture.mlximg, &junk, &junk, &junk);
	if (!(d->anim[0] = new_anim(d, SF_FRAMES - 1, "./textures/SF2/", 0)))
		err_exit(d, 10, "mlx_xpm_file_to_image has failed", EXIT_FAILURE);
	d->textures[1][0] = *d->anim[0];
	if (!(d->anim[1] = new_anim(d, PIKA_FRAMES - 1, "./textures/pika/", 0)))
		err_exit(d, 11, "mlx_xpm_file_to_image has failed", EXIT_FAILURE);
	d->textures[2][0] = *d->anim[1];
	if (!(d->anim[2] = new_anim(d, SF_FRAMES - 1, "./textures/chun_li/", 0)))
		err_exit(d, 12, "mlx_xpm_file_to_image has failed", EXIT_FAILURE);
	d->textures[3][0] = *d->anim[2]->next->next->next->next->next->next
		->next->next->next->next->next->next->next->next->next->next;
	duplicate_faces(d->textures[1]);
	duplicate_faces(d->textures[2]);
	duplicate_faces(d->textures[3]);
	random_map(d, random);
}

void	load_textures(t_data *d)
{
	short random;

	random = ((intptr_t) & d->mlx / 10000) % 4;
	d->fog_color = (int[4]){0x433881, 0xe4b8dd, 0xffffff, 0x216c73}[random];
	if (!(d->textures[0][NORTH].mlximg =
				mlx_xpm_file_to_image(d->mlx, "./textures/north.xpm",
					&d->textures[0][NORTH].w, &d->textures[0][NORTH].h)))
		err_exit(d, 5, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);
	if (!(d->textures[0][SOUTH].mlximg =
				mlx_xpm_file_to_image(d->mlx, "./textures/south.xpm",
					&d->textures[0][SOUTH].w, &d->textures[0][SOUTH].h)))
		err_exit(d, 6, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);
	if (!(d->textures[0][EAST].mlximg =
				mlx_xpm_file_to_image(d->mlx, "./textures/east.xpm",
					&d->textures[0][EAST].w, &d->textures[0][EAST].h)))
		err_exit(d, 7, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);
	if (!(d->textures[0][WEST].mlximg =
				mlx_xpm_file_to_image(d->mlx, "./textures/west.xpm",
					&d->textures[0][WEST].w, &d->textures[0][WEST].h)))
		err_exit(d, 8, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);
	if (!(d->sky_texture.mlximg = mlx_xpm_file_to_image(d->mlx,
					get_xpm_pos(random, "textures/sky/")
					, &d->sky_texture.w, &d->sky_texture.h)))
		err_exit(d, 9, "mlx_xmp_file_to_image has failed", EXIT_FAILURE);
	load_textures_2(d, (short)random);
}
