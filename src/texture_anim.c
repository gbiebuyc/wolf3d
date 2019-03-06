/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:20:07 by nallani           #+#    #+#             */
/*   Updated: 2019/03/06 19:26:46 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	get_xpm_pos(int i, char *str, char **full_path)
{
	int		size_of_i;
	int		tmp;
	char	*itoa_nb;

	tmp = i;
	if (!(itoa_nb = ft_itoa(i)))
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	size_of_i = ft_strlen(itoa_nb);
	size_of_i++;
	if (!(full_path[0] = (char *)malloc(sizeof(char) *
					ft_strlen(str) + size_of_i + 4)))
	{
		perror("malloc_error:");
		exit(EXIT_FAILURE);
	}
	tmp = -1;
	while (str[++tmp])
		full_path[0][tmp] = str[tmp];
	full_path[0][tmp] = 0;
	ft_strcat(full_path[0], itoa_nb);
	free(itoa_nb);
	ft_strcat(full_path[0], ".xpm");
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
	char			*str;
	int				junk;

	i = 0;
	while (i < 4)
	{
		get_xpm_pos(i, "./textures/pika/", &str);
		if (!(a[i].mlximg = mlx_xpm_file_to_image(d->mlx, str,
						&a[i].w, &a[i].h)))
		{
			perror("mlx_xpm_file_to_image");
			exit(EXIT_FAILURE);
		}
		a[i].pixels = (uint32_t*)mlx_get_data_addr(a[i].mlximg, &junk,
				&junk, &junk);
		ft_bzero(str, ft_strlen(str));
		ft_strdel(&str);
		if (i != 3)
			a[i].next = &a[i + 1];
		i++;
	}
	a[3].next = &a[0];
	d->textures[1][0] = a[0];
}

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
		ft_bzero(str, ft_strlen(str));
		ft_strdel(&str);
		if (i != 21)
			a[i].next = &a[i + 1];
		i++;
	}
	a[21].next = &a[0];
	d->textures[2][0] = a[0];
}
