/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <cmarteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:44:30 by marvin            #+#    #+#             */
/*   Updated: 2021/09/15 15:44:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_textdef(int y, int x, t_cub3d *data)
{
	if (data->side == 0)
		data->exact_x = data->y + data->distowall * data->rayy;
	else
		data->exact_x = data->x + data->distowall * data->rayx;
	data->exact_x = data->exact_x - (int)(data->exact_x);
	if (y >= data->walltop && y < data->wallbottom && data->side == 0 \
		&& data->rayx < 0)
		ft_textdef_ns(y, x, data, 'N');
	else if (y >= data->walltop && y < data->wallbottom && data->side == 0 \
		&& data->rayx >= 0)
		ft_textdef_ns(y, x, data, 'S');
	else if (y >= data->walltop && y < data->wallbottom && data->side == 1 \
		&& data->rayy < 0)
		ft_textdef_ew(y, x, data, 'W');
	else if (y >= data->walltop && y < data->wallbottom && data->side == 1 \
		&& data->rayy >= 0)
		ft_textdef_ew(y, x, data, 'E');
	else if (y >= data->wallbottom)
		data->addr[y * data->width + x] = data->floor_color;
	else
		data->addr[y * data->width + x] = data->ceiling_color;
}

void	ft_textdef_ns(int y, int x, t_cub3d *data, char c)
{
	if (c == 'N')
	{
		data->tex_x = (int)(data->exact_x * data->no_tex.width);
		data->tex_y = (y - data->walltop) * \
		data->no_tex.height / data->wallheight;
		data->addr[y * data->width + x] = \
		data->no_tex.tex.addr[data->tex_y * data->no_tex.width + data->tex_x];
	}
	else
	{
		data->tex_x = (int)(data->exact_x * data->so_tex.width);
		data->tex_y = (y - data->walltop) * \
		data->so_tex.height / data->wallheight;
		data->addr[y * data->width + x] = \
		data->so_tex.tex.addr[data->tex_y * data->so_tex.width + data->tex_x];
	}
}

void	ft_textsprite(t_cub3d *data, t_sprite *sprite)
{
	int		x;
	int		y;
	float	d;
	int		id;

	x = ft_truc(sprite->left);
	while (++x < sprite->right)
	{
		sprite->t_x = round((256 * (x - (-(float)sprite->w / 2 + \
		sprite->spritescreenx)) * data->sp_tex.width / sprite->w) / 256);
		if (sprite->d > 0 && x > 0 && \
				x < data->width && sprite->d < data->zbuffer[x])
		{
			y = ft_truc(sprite->top);
			while (++y < sprite->bottom && y < data->height)
			{
				d = y * 256 - data->height * 128 + sprite->h * 128;
				sprite->t_y = round(((d * data->sp_tex.height) / sprite->h) \
				/ 256);
				id = sprite->t_y * data->sp_tex.width + sprite->t_x;
				if (data->sp_tex.tex.addr[id] != 0)
					data->addr[y * data->width + x] = data->sp_tex.tex.addr[id];
			}
		}
	}
}

void	ft_def_tex(t_tex tex, char c, t_cub3d *data, char *str)
{
	if (c == 'n')
		data->no_tex = tex;
	if (c == 'o')
		data->we_tex = tex;
	if (c == 'e')
		data->ea_tex = tex;
	if (c == 'u')
		data->so_tex = tex;
	if (c == 's')
		data->sp_tex = tex;
	free(str);
}

void	ft_parsing_tex(char *line, char c, t_cub3d *data)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = ft_search_char(line, 'N');
	j = ft_search_char(line, 'W');
	l = ft_search_char(line, 'E');
	k = ft_search_char(line, 'S');
	if (i >= 0 && c == 'n' && line[i + 1] == 'O')
		ft_texture(line, data, c);
	if (j >= 0 && c == 'o' && line[j + 1] == 'E')
		ft_texture(line, data, c);
	if (l >= 0 && c == 'e' && line[l + 1] == 'A')
		ft_texture(line, data, c);
	if (k >= 0 && c == 'u' && line[k + 1] == 'O')
		ft_texture(line, data, c);
	if (k >= 0 && c == 's' && line[k + 1] == ' ')
	{
		while (line[k] && line[k] != '.')
			k++;
		if (line[k] == '.')
			ft_texture(line, data, c);
	}
}
