/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:57:28 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/17 17:33:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_search_char(char *s, char c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_parsing(char *map, char c, t_cub3d *data)
{
	int			fd;
	char		*line;
	static char	*tmp;

	tmp = NULL;
	line = NULL;
	data->assigned = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		ft_error_tex(NULL, 10, data);
	while (get_next_line(fd, &line) > 0)
	{
		ft_parsing_params(line, c, data);
		tmp = ft_parsing_mapo(line, c, fd, tmp);
		free(line);
		line = 0;
	}
	if (tmp)
		data->mapo = ft_split(tmp, '\n', data, line);
	else
		data->mapo = 0;
	free(tmp);
	free(line);
	close(fd);
}

int	ft_width(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = ft_skip_space(line, 0);
	while (line[++i])
	{
		if (!(line[i] == ' ' || line[i] == ',' || \
			(line[i] >= '0' && line[i] <= '9')))
		{
			free(line);
			ft_error(11);
		}
	}
	i = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	j = i;
	while (line[j] >= '0' && line[j] <= '9' && line[i])
		j++;
	str = ft_substr(line, i, j - i);
	i = ft_atoi(str);
	free(str);
	return (i);
}

int	ft_height(char *line)
{
	int		i;
	int		j;
	int		nb;
	char	*str;

	i = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9' && line[i])
		i++;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	j = i;
	while (line[j] >= '0' && line[j] <= '9' && line[i])
		j++;
	str = ft_substr(line, i, j - i);
	nb = ft_atoi(str);
	free(str);
	return (nb);
}

void	ft_texture(char *line, t_cub3d *data, char c)
{
	int		i;
	int		j;
	char	*str;
	t_tex	tex;

	i = 0;
	while (!(line[i] == 'N' || line[i] == 'S' || \
		line[i] == 'W' || line[i] == 'E'))
		i++;
	i += 2;
	while (line[i] == ' ' && line[i])
		i++;
	if (line[i] != '.')
		ft_error_tex(line, 6, data);
	j = i;
	while (line[j])
		j++;
	str = ft_substr(line, i, j - i);
	tex.tex.img = mlx_xpm_file_to_image(data->mlx_ptr, \
	str, &tex.width, &tex.height);
	if (tex.tex.img == NULL)
		ft_tex_err(str, line, data);
	tex.tex.addr = (int *)mlx_get_data_addr(tex.tex.img, \
	&(tex.tex.bits_per_pixel), &(tex.tex.line_length), &(tex.tex.endian));
	ft_def_tex(tex, c, data, str);
}
