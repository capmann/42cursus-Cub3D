/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:36:56 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/09 16:39:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(const char *s1)
{
	char			*memory;
	unsigned int	i;
	unsigned int	len_s1;

	i = 0;
	len_s1 = ft_strlen(s1);
	memory = malloc(sizeof(char) * (len_s1 + 1));
	if (!memory)
		return (0);
	while (s1[i])
	{
		memory[i] = s1[i];
		i++;
	}
	memory[i] = '\0';
	return (memory);
}

void	ft_distowall(t_cub3d *data)
{
	if (data->side == 0)
		data->distowall = (data->mapx - data->x + \
		(1 - data->stepx) / 2) / data->rayx;
	else
		data->distowall = (data->mapy - data->y + \
		(1 - data->stepy) / 2) / data->rayy;
}

void	ft_new_sprite(t_cub3d *data, t_sprite *new)
{
	t_sprite	*iter;
	t_sprite	*tmp;

	iter = data->list.first;
	tmp = data->list.first;
	if (iter->d <= new->d)
	{
		new->next = data->list.first;
		data->list.first = new;
	}
	else
	{
		while (iter->d > new->d && iter->next && iter)
			iter = iter->next;
		while (tmp->next != iter && tmp->next)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	ft_free_split(char *line, char *str, char **tab, t_cub3d *data)
{
	free(line);
	free(str);
	ft_free_table(tab);
	close_window(data);
}

void	ft_tex_err(char *str, char *line, t_cub3d *data)
{
	free(str);
	ft_error_tex(line, 6, data);
}
