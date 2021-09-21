/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:02:30 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/06 21:44:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lateral_right(t_cub3d *data)
{
	data->speed = 0.1;
	if (data->mapo[(int)(data->x + \
	data->camplanex * data->speed)][(int)(data->y)] != '1' && \
	data->mapo[(int)(data->x)][(int)(data->y + data->camplaney * data->speed)] \
	!= '1')
		data->x += data->camplanex * data->speed;
	if (data->mapo[(int)(data->x)][(int)(data->y + \
	data->camplaney * data->speed)] != '1' && \
	data->mapo[(int)(data->x + data->camplanex * data->speed)][(int)(data->y)] \
	!= '1')
		data->y += data->camplaney * data->speed;
}

void	ft_lateral_left(t_cub3d *data)
{
	data->speed = 0.1;
	if (data->mapo[(int)(data->x - \
	data->camplanex * data->speed)][(int)(data->y)] != '1' && \
	data->mapo[(int)(data->x)][(int)(data->y - data->camplaney * data->speed)] \
	!= '1')
		data->x -= data->camplanex * data->speed;
	if (data->mapo[(int)(data->x)][(int)(data->y - \
	data->camplaney * data->speed)] != '1' && \
	data->mapo[(int)(data->x - data->camplanex * data->speed)][(int)(data->y)] \
	!= '1')
		data->y -= data->camplaney * data->speed;
}

int	ft_truc(int i)
{
	int	a;

	a = 0;
	if (i < 0)
		a = 0;
	else
		a = i;
	return (a);
}

void	ft_textdef_ew(int y, int x, t_cub3d *data, char c)
{
	if (c == 'W')
	{
		data->tex_x = (int)(data->exact_x * data->we_tex.width);
		data->tex_y = (y - data->walltop) * \
		data->we_tex.height / data->wallheight;
		data->addr[y * data->width + x] = \
		data->we_tex.tex.addr[data->tex_y * data->we_tex.width + data->tex_x];
	}
	else
	{
		data->tex_x = (int)(data->exact_x * data->ea_tex.width);
		data->tex_y = (y - data->walltop) * \
		data->ea_tex.height / data->wallheight;
		data->addr[y * data->width + x] = \
		data->ea_tex.tex.addr[data->tex_y * data->ea_tex.width + data->tex_x];
	}
}

int	ft_skip_space(char *str, int i)
{
	while (str[i] == ' ' && str[i])
		i++;
	return (i);
}
