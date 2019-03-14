/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 21:52:27 by nallani           #+#    #+#             */
/*   Updated: 2019/03/14 21:24:41 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_length(int x, short mod)
{
	static int	max_x;

	if (mod)
	{
		if (!(max_x))
			max_x = -1;
		if (max_x == -1)
			max_x = x;
		if (!(x) || max_x != x)
		{
			ft_putstr_fd("invalid_map\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	return (max_x);
}

void	check_str(char *str)
{
	char	*good_chars;
	int		i;
	int		j;

	good_chars = GOOD_CHARS;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (good_chars[j])
		{
			if (good_chars[j] == str[i])
				break ;
			j++;
		}
		if (!(good_chars[j]))
		{
			ft_putstr_fd("invalid_characters_in_map\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	error_test(int i, int mod, int *fd, char *path)
{
	if (i < 0)
	{
		ft_putstr_fd("get_next_line_fail\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!(mod))
		if ((*fd = open(path, O_RDONLY)) < 0)
		{
			perror("open_map");
			exit(EXIT_FAILURE);
		}
}

void	init_map_2(t_data *d, char *map, unsigned int count, int fd)
{
	int		i;
	char	*str;
	char	*tmp;

	while ((i = get_next_line(fd, &str) > 0))
	{
		tmp = map;
		if (!(map = ft_strjoin(map, str)))
		{
			perror("ft_strejoin");
			exit(EXIT_FAILURE);
		}
		if (count)
			free(tmp);
		free(str);
		count++;
	}
	error_test(i, 1, NULL, NULL);
	d->map = map;
}

void	init_map(t_data *d, char *map, int count, int fd)
{
	int		i;
	char	*str;

	error_test(0, 0, &fd, d->map_path);
	while ((i = get_next_line(fd, &str) > 0))
	{
		check_length(ft_strlen(str), 1);
		check_str(str);
		count++;
		free(str);
	}
	error_test(i, 1, NULL, NULL);
	d->mapsize.x = check_length(-1, 0);
	d->mapsize.y = count;
	close(fd);
	error_test(0, 0, &fd, d->map_path);
	init_map_2(d, map, 0, fd);
}
