/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:04:47 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/15 22:57:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parsing_player(t_cub3d *data)
{
	int	x;
	int	y;

	x = -1;
	while (data->mapo[++x])
	{
		y = -1;
		while (data->mapo[x][++y])
		{
			if (data->mapo[x][y] == 'N' || data->mapo[x][y] == 'W' || \
				data->mapo[x][y] == 'E' || data->mapo[x][y] == 'S')
			{
				data->x = x + 0.5;
				data->y = y + 0.5;
			}
		}		
	}
	if (!data->x || !data->y)
	{
		ft_pustr("Error\nInvalid map - No player detected");
		close_window(data);
	}
}

void	ft_parsing_dir(t_cub3d *data)
{
	char	c;

	c = data->mapo[(int)data->x][(int)data->y];
	if (c == 'N')
	{
		data->dirvecx = -1;
		data->dirvecy = 0;
	}
	if (c == 'S')
	{
		data->dirvecx = 1;
		data->dirvecy = 0;
	}
	if (c == 'E')
	{
		data->dirvecx = 0;
		data->dirvecy = 1;
	}
	if (c == 'W')
	{
		data->dirvecx = 0;
		data->dirvecy = -1;
	}
}

void	ft_parsing_cam(t_cub3d *data)
{
	char	c;

	c = data->mapo[(int)data->x][(int)data->y];
	if (c == 'N')
	{
		data->camplanex = 0;
		data->camplaney = 0.66;
	}
	if (c == 'S')
	{
		data->camplanex = 0;
		data->camplaney = -0.66;
	}
	if (c == 'E')
	{
		data->camplanex = 0.66;
		data->camplaney = 0;
	}
	if (c == 'W')
	{
		data->camplanex = -0.66;
		data->camplaney = 0;
	}
}

void	ft_parsing_params(char *line, char c, t_cub3d *data)
{
	int	i;
	int	k;
	int	l;

	i = 0;
	k = ft_search_char(line, 'F');
	l = ft_search_char(line, 'C');
	ft_check_multiple_assignement(line, data);
	if (k >= 0 && line[k + 1] == ' ' && c == 'f')
		data->floor_color = ft_color(line);
	if (l >= 0 && line[l + 1] == ' ' && c == 'c')
		data->ceiling_color = ft_color(line);
	ft_parsing_tex(line, c, data);
	while (line[i] && line[i] == ' ')
		i++;
	if (!(line[i] == 'S' || line[i] == 'N' || line[i] == 'E' \
		|| line[i] == 'W' || line[i] == 'F' || line[i] == 'C' || line[i] == '1' \
		|| line[i] == '0' || line[i] == 0))
		ft_error_tex(line, 10, data);
}

char	*ft_parsing_mapo(char *line, char c, int fd, char *tmp)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if ((line[i] == '1') && c == 'm')
	{
		tmp = ft_strjoin(tmp, line);
		tmp = ft_strjoin(tmp, "\n");
		while (get_next_line(fd, &line) > 0)
		{
			tmp = ft_strjoin(tmp, line);
			tmp = ft_strjoin(tmp, "\n");
			free(line);
			line = 0;
		}
		tmp = ft_strjoin(tmp, line);
		tmp = ft_strjoin(tmp, "\n");
		free(line);
		line = 0;
	}
	return (tmp);
}
