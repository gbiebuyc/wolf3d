/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:20:07 by nallani           #+#    #+#             */
/*   Updated: 2019/03/12 19:44:47 by nallani          ###   ########.fr       */
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
		perror("error");
		exit(EXIT_FAILURE);
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

void	anim_pika(t_data *d)
{
	int				i;
	static t_img	a[4];
	int				junk;

	i = 0;
	while (i < 4)
	{
		if (!(a[i].mlximg = mlx_xpm_file_to_image(d->mlx, get_xpm_pos(i, "./textures/pika/"),
						&a[i].w, &a[i].h)))
		{
			perror("mlx_xpm_file_to_image");
			exit(EXIT_FAILURE);
		}
		a[i].pixels = (uint32_t*)mlx_get_data_addr(a[i].mlximg, &junk,
				&junk, &junk);
		if (i != 3)
			a[i].next = &a[i + 1];
		i++;
	}
	a[3].next = &a[0];
	d->textures[1][0] = a[0];
}
/*
void	anim_ryu(t_data *d)
{
	int				i;
	static t_img	a[22];
	char			*str;
	int				junk;

	i = 0;
	while (i < 22)
	{
		get_xpm_pos(i, "./textures/SF2/", &str);
		if (!(a[i].mlximg = mlx_xpm_file_to_image(d->mlx, str,
						&a[i].w, &a[i].h)))
		{
			perror("mlx_xpm_file_to_image");
			exit(EXIT_FAILURE);
		}
		a[i].pixels = (uint32_t*)mlx_get_data_addr(a[i].mlximg, &junk,
				&junk, &junk);
		ft_strdel(&str);
		if (i != 21)
			a[i].next = &a[i + 1];
		i++;
	}
	a[21].next = &a[0];
	d->textures[2][0] = a[0];
}
*/
t_img	*new_anim(t_data *d, short nb_of_frames, char *path)
{
	short			i;
	t_img			*a[3];
	int				junk;

	i = nb_of_frames;
	a[1] = NULL;
	while (i >= 0)
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
			free(a);
			perror("mlx_xpm_file_to_image");
			exit(EXIT_FAILURE);
		}
		a[0]->pixels = (uint32_t*)mlx_get_data_addr(a[0]->mlximg, &junk,
				&junk, &junk);
		printf("%d\n", i);
		i--;
	}
	a[2]->next = a[0];
	return (a[0]);
}
