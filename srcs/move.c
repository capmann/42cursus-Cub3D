/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:26:19 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/06 21:10:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_key(t_cub3d *data)
{
	if (ft_key_check(&data->keys, 65307) || (ft_key_check(&data->keys, 120)))
		close_window(data);
	if (ft_key_check(&data->keys, 119))
		ft_forward(data);
	if (ft_key_check(&data->keys, 115))
		ft_backward(data);
	if (ft_key_check(&data->keys, 97))
		ft_lateral_left(data);
	if (ft_key_check(&data->keys, 100))
		ft_lateral_right(data);
	if (ft_key_check(&data->keys, 65363))
		ft_right(data);
	if (ft_key_check(&data->keys, 65361))
		ft_left(data);
}

void	ft_forward(t_cub3d *data)
{
	data->speed = 0.1;
	if (data->mapo[(int)(data->x + \
	data->dirvecx * data->speed)][(int)(data->y)] != '1' && \
	data->mapo[(int)(data->x)][(int)(data->y + data->dirvecy * data->speed)] \
	!= '1')
		data->x += data->dirvecx * data->speed;
	if (data->mapo[(int)(data->x)][(int)(data->y + \
	data->dirvecy * data->speed)] != '1' && \
	data->mapo[(int)(data->x + data->dirvecx * data->speed)][(int)(data->y)] \
	!= '1')
		data->y += data->dirvecy * data->speed;
}

void	ft_backward(t_cub3d *data)
{
	data->speed = 0.1;
	if (data->mapo[(int)(data->x - \
	data->dirvecx * data->speed)][(int)(data->y)] != '1' && \
	data->mapo[(int)(data->x)][(int)(data->y - data->dirvecy * data->speed)] \
	!= '1')
		data->x -= data->dirvecx * data->speed;
	if (data->mapo[(int)(data->x)][(int)(data->y - \
	data->dirvecy * data->speed)] != '1' && \
	data->mapo[(int)(data->x - data->dirvecx * data->speed)][(int)(data->y)] \
	!= '1')
		data->y -= data->dirvecy * data->speed;
}

void	ft_right(t_cub3d *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirvecx;
	data->dirvecx = data->dirvecx * cos(-0.1) - data->dirvecy * sin(-0.1);
	data->dirvecy = olddirx * sin(-0.1) + data->dirvecy * cos(-0.1);
	oldplanex = data->camplanex;
	data->camplanex = data->camplanex * cos(-0.1) - data->camplaney * sin(-0.1);
	data->camplaney = oldplanex * sin(-0.1) + data->camplaney * cos(-0.1);
}

void	ft_left(t_cub3d *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirvecx;
	data->dirvecx = data->dirvecx * cos(0.1) - data->dirvecy * sin(0.1);
	data->dirvecy = olddirx * sin(0.1) + data->dirvecy * cos(0.1);
	oldplanex = data->camplanex;
	data->camplanex = data->camplanex * cos(0.1) - data->camplaney * sin(0.1);
	data->camplaney = oldplanex * sin(0.1) + data->camplaney * cos(0.1);
}
