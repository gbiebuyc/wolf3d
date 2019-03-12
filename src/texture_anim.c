/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:20:07 by nallani           #+#    #+#             */
/*   Updated: 2019/03/12 22:49:51 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*get_xpm_pos(int i, char *str)
{
	int				size_of_i;
	int				tmp;
	char			*itoa_nb;
	static	char	full_path[MAX_SIZE_OF_PATH];

	tmp = i;
	ft_bzero(full_path, MAX_SIZE_OF_PATH);
	if (!(itoa_nb = ft_itoa(i)))
	{
		perror("ft_itoa");
		exit(EXIT_FAILURE);
		// return null ?
	}
	size_of_i = ft_strlen(itoa_nb) + 1;
	tmp = -1;
	while (str[++tmp])
		full_path[tmp] = str[tmp];
	ft_strcat(full_path, itoa_nb);
	free(itoa_nb);
	ft_strcat(full_path, ".xpm");
	return (full_path);
}

void	duplicate_faces(t_img *img)
{
	int		i;

	i = NORTH;
	while (++i <= WEST)
		img[i] = img[NORTH];
}

t_img	*new_anim(t_data *d, short nb_of_frames, char *path, int junk)
{
	short			i;
	t_img			*a[3];

	i = nb_of_frames + 1;
	a[1] = NULL;
	while (--i >= 0)
	{
		if (!(a[0] = (t_img *)malloc(sizeof(t_img))))
			;//do error
		if (i == nb_of_frames)
			a[2] = a[0];
		a[0]->next = a[1];
		a[1] = a[0];
		if (!(a[0]->mlximg = mlx_xpm_file_to_image(d->mlx, get_xpm_pos(i, path),
						&a[0]->w, &a[0]->h)))
		{
			free(a[0]);
			perror("mlx_xpm_file_to_image");
			exit(EXIT_FAILURE);
		}
		a[0]->pixels = (uint32_t*)mlx_get_data_addr(a[0]->mlximg, &junk,
				&junk, &junk);
	}
	a[2]->next = a[0];
	return (a[0]);
}
