/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 01:38:41 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/13 17:05:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_keys(t_cub3d *data)
{
	t_key	*tmp;
	t_key	*tmp2;

	tmp = data->keys.first;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void	ft_free_all(t_cub3d *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->no_tex.tex.img)
		mlx_destroy_image(data->mlx_ptr, data->no_tex.tex.img);
	if (data->so_tex.tex.img)
		mlx_destroy_image(data->mlx_ptr, data->so_tex.tex.img);
	if (data->we_tex.tex.img)
		mlx_destroy_image(data->mlx_ptr, data->we_tex.tex.img);
	if (data->ea_tex.tex.img)
		mlx_destroy_image(data->mlx_ptr, data->ea_tex.tex.img);
	if (data->sp_tex.tex.img)
		mlx_destroy_image(data->mlx_ptr, data->sp_tex.tex.img);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	if (data->mapo)
		ft_free_table(data->mapo);
}

int	close_window(t_cub3d *data)
{
	ft_free_all(data);
	ft_free_keys(data);
	exit(0);
}

int	key_press(int keycode, t_cub3d *data)
{
	t_key	*key;

	if (keycode == 65307)
		return (close_window(data));
	if (!ft_key_check(&data->keys, keycode))
	{
		key = ft_new_key(keycode);
		ft_key_addfront(&data->keys, key);
	}
	return (keycode);
}

void	ft_free_table(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
