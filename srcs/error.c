/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:20:28 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/17 17:37:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pustr(char *str)
{
	int	i;
	int	w;

	i = 0;
	while (str[i])
		i++;
	w = write(1, str, i);
	(void)w;
}

void	ft_error(int a)
{
	int		fd;
	char	*line;

	fd = open("srcs/error.c", O_RDONLY);
	ft_write_error(a);
	if (a != 1)
	{
		while (get_next_line(fd, &line) > 0)
			free(line);
		free(line);
		close(fd);
	}
	if (a != 6 && a != 4 && a != 10 && a != 5 && a != 7 && a != 8)
		exit(0);
}

void	ft_error_map1(t_cub3d *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (data->mapo[0][++j])
		if (!(data->mapo[0][j] == '1' || data->mapo[0][j] == ' '))
			ft_error_tex(NULL, 4, data);
	while (data->mapo[++i])
	{
		j = 0;
		while (data->mapo[i][j] == ' ' && data->mapo[i][j])
			j++;
		if (!(data->mapo[i][j] == '1' || data->mapo[i][j] == '\0'))
			ft_error_tex(NULL, 4, data);
	}
	i = i - 1;
	j = -1;
	while (data->mapo[i][++j])
	{
		if (!(data->mapo[i][j] == '1' || data->mapo[i][j] == ' '))
			ft_error_tex(NULL, 4, data);
	}
	ft_error_map2(data);
}

void	ft_error_params(t_cub3d *data)
{
	if (!data->height || !data->width)
	{
		ft_error(5);
		close_window(data);
	}
	if (data->width > 2560)
		data->width = 2560;
	if (data->height > 1440)
		data->height = 1440;
	if (data->floor_color < 0 || data->ceiling_color < 0)
	{
		ft_error(8);
		close_window(data);
	}
	if (!data->no_tex.width || !data->so_tex.width || !data->we_tex.width || \
		 !data->ea_tex.width)
	{
		ft_error(6);
		close_window(data);
	}
}

void	ft_map_check(char *line, t_cub3d *data)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == ' ')
			line[i] = '1';
	i = 0;
	while (line[i] == '0' || line[i] == '1' || line[i] == ' ' \
	|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		i++;
	if (line[i])
	{
		ft_error(10);
		close_window(data);
	}
	i = -1;
	while (line[++i])
		if (line[i] == 'N' || line[i] == 'E' || line[i] == 'W' || \
			line[i] == 'S')
			data->flag++;
	if (!(data->flag == 1 || data->flag == 0))
	{
		ft_pustr("Error\nInvalid map - Multiple player detected");
		close_window(data);
	}
}
