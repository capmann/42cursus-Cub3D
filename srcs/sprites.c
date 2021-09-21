/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:02:45 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/14 18:24:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*ft_sprite(t_cub3d *data)
{
	double		invdet;
	double		transformx;
	double		x;
	double		y;
	t_sprite	*new;

	new = malloc(sizeof(t_sprite));
	if (!new)
		return (NULL);
	x = data->mapx - data->x + 0.5;
	y = data->mapy - data->y + 0.5;
	invdet = 1.0 / \
	(data->camplanex * data->dirvecy - data->dirvecx * data->camplaney);
	transformx = invdet * (data->dirvecy * x - data->dirvecx * y);
	new->d = invdet * (-data->camplaney * x + data->camplanex * y);
	new->spritescreenx = (int) \
	((data->width / 2) * (1 + transformx / new->d));
	new->h = abs((int)(data->height / new->d));
	ft_sprite_limits(data, new);
	new->x = data->mapx;
	new->y = data->mapy;
	new->next = NULL;
	return (new);
}

void	ft_sprite_limits(t_cub3d *data, t_sprite *new)
{
	new->top = -new->h / 2 + data->height / 2;
	if (new->top < 0)
		new->top = 0;
	new->bottom = new->h / 2 + data->height / 2;
	if (new->bottom >= data->height)
		new->bottom = data->height - 1;
	new->w = abs((int)((data->height) / new->d));
	new->left = -new->w / 2 + new->spritescreenx;
	if (new->left < 0)
		new->left = 0;
	new->right = new->w / 2 + new->spritescreenx;
	if (new->right >= data->width)
		new->right = data->width - 1;
}

void	ft_sprite_loop(t_cub3d *data)
{
	t_sprite	*new;

	if (data->list.first == NULL)
	{
		new = ft_sprite(data);
		data->list.first = new;
	}
	else
	{
		new = data->list.first;
		while (new->next)
		{
			if (new->x == data->mapx && new->y == data->mapy)
				return ;
			else
				new = new->next;
		}
		new = ft_sprite(data);
		ft_new_sprite(data, new);
	}
}

void	ft_draw_sprite(t_cub3d *data)
{
	t_sprite	*sprite;

	sprite = data->list.first;
	while (sprite)
	{
		ft_textsprite(data, sprite);
		if (sprite->next && !sprite->next->next)
			break ;
		sprite = sprite->next;
	}
	ft_free_list(&data->list);
}

void	ft_free_list(t_list *list)
{
	t_sprite	*tmp;
	t_sprite	*tmp2;

	tmp = list->first;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}
