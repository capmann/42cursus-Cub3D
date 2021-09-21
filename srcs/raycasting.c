/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:02:57 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/15 15:47:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycasting(t_cub3d *data)
{
	int		count_h;
	int		count_w;
	double	distowall;

	count_w = -1;
	data->zbuffer = malloc(sizeof(double) * (data->width + 1));
	if (!data->zbuffer)
		return ;
	data->list.first = NULL;
	while (++count_w < data->width)
	{
		data->camx = 2 * count_w / (double)(data->width) - 1;
		ft_definition(data);
		ft_raydef(data);
		distowall = ft_calcul_distowall(data);
		ft_wall_limits(data);
		count_h = -1;
		while (++count_h < data->height)
			ft_textdef(count_h, count_w, data);
		data->zbuffer[count_w] = distowall;
	}
	free(data->zbuffer);
}

void	ft_wall_limits(t_cub3d *data)
{
	int		half_screen;

	half_screen = data->height / 2;
	data->wallheight = (int)(data->height / data->distowall);
	data->walltop = -data->wallheight / 2 + half_screen;
	data->wallbottom = data->wallheight / 2 + half_screen;
	if (data->wallbottom >= data->height)
		data->wallbottom = data->height - 1;
	if (data->wallbottom < 0)
		data->wallbottom = data->height;
}

void	ft_definition(t_cub3d *data)
{
	data->rayx = data->dirvecx + data->camplanex * data->camx;
	data->rayy = data->dirvecy + data->camplaney * data->camx;
	data->mapx = (int)(data->x);
	data->mapy = (int)(data->y);
	data->deltadistx = fabs(1 / data->rayx);
	data->deltadisty = fabs(1 / data->rayy);
	data->wall = 0;
}

void	ft_raydef(t_cub3d *data)
{
	if (data->rayx < 0)
	{
		data->stepx = -1;
		data->distox = (data->x - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->distox = (data->mapx + 1 - data->x) * data->deltadistx;
	}
	if (data->rayy < 0)
	{
		data->stepy = -1;
		data->distoy = (data->y - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->distoy = (data->mapy + 1 - data->y) * data->deltadisty;
	}
}

double	ft_calcul_distowall(t_cub3d *data)
{
	while (data->wall == 0)
	{
		if (data->distox < data->distoy)
		{
			data->distox += data->deltadistx;
			data->mapx += data->stepx;
			data->side = 0;
		}
		else
		{
			data->distoy += data->deltadisty;
			data->mapy += data->stepy;
			data->side = 1;
		}
		if (data->mapo[data->mapx][data->mapy] == '1')
			data->wall = 1;
	}
	ft_distowall(data);
	return (data->distowall);
}
