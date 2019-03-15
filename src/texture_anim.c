/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:20:07 by nallani           #+#    #+#             */
/*   Updated: 2019/03/15 13:35:22 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*get_xpm_pos(int i, char *str)
{
	int				tmp;
	char			*itoa_nb;
	static	char	full_path[MAX_SIZE_OF_PATH];

	tmp = i;
	ft_bzero(full_path, MAX_SIZE_OF_PATH);
	itoa_nb = ft_itoa_static(i);
	tmp = -1;
	while (str[++tmp])
		full_path[tmp] = str[tmp];
	ft_strcat(full_path, itoa_nb);
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

t_img	*error_new_anim(t_img *start, int mod, t_img *last, void *mlx)
{
	if (mod)
		free(last);
	if (!(start))
		return (NULL);
	last = start;
	while (last)
	{
		start = last;
		last = start->next;
		mlx_destroy_image(mlx, start->mlximg);
		free(start);
	}
	return (NULL);
}

t_img	*new_anim(t_data *d, short nb_of_frames, char *path, int junk)
{
	short			i;
	t_img			*a[3];

	i = nb_of_frames + 1;
	a[0] = NULL;
	a[1] = NULL;
	a[2] = NULL;
	while (--i >= 0)
	{
		if (!(a[0] = (t_img *)malloc(sizeof(t_img))))
			return (error_new_anim(a[1], 0, a[0], d->mlx));
		if (i == nb_of_frames)
			a[2] = a[0];
		a[0]->next = a[1];
		a[1] = a[0];
		if (!(a[0]->mlximg = mlx_xpm_file_to_image(d->mlx, get_xpm_pos(i, path),
						&a[0]->w, &a[0]->h)))
			return (error_new_anim(a[1]->next, 1, a[0], d->mlx));
		a[0]->pixels = (uint32_t*)mlx_get_data_addr(a[0]->mlximg, &junk,
				&junk, &junk);
	}
	a[2]->next = a[0];
	return (a[0]);
}
