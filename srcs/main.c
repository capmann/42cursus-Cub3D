/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 15:40:08 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/15 19:56:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_game(t_cub3d *data, char *map)
{
	data->floor_color = -1;
	data->ceiling_color = -1;
	ft_parsing(map, 'f', data);
	ft_parsing(map, 'c', data);
	data->height = 1000;
	data->width = 1000;
}

void	ft_parsing_map(t_cub3d *data, char *map)
{
	int	i;

	i = -1;
	data->flag = 0;
	data->size_max = 0;
	ft_parsing(map, 'n', data);
	ft_parsing(map, 'o', data);
	ft_parsing(map, 'e', data);
	ft_parsing(map, 'u', data);
	ft_parsing(map, 'm', data);
	if (!data->mapo)
	{
		ft_pustr("Error\nMap not available");
		close_window(data);
	}
	ft_parsing_player(data);
	ft_parsing_dir(data);
	ft_parsing_cam(data);
	ft_error_params(data);
	ft_error_map1(data);
	while (data->mapo[++i])
	{
		ft_map_check(data->mapo[i], data);
		ft_empty_line(data->mapo[i]);
	}
}

int	my_mlx_image(t_cub3d *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->addr = (int *)mlx_get_data_addr(data->img, \
	&data->bits_per_pixel, &data->line_length, &data->endian);
	ft_key(data);
	ft_raycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}

int	main(int ac, char **ag)
{
	t_cub3d	data;
	char	*map;
	int		i;

	data = (t_cub3d){};
	if (ac <= 1 || ac >= 3)
		ft_error(1);
	map = ag[1];
	i = 0;
	while (map[i])
		i++;
	if (!(map[i - 1] == 'b' && map[i - 2] == 'u' && map[i - 3] == 'c' && \
		map[i - 4] == '.'))
		ft_error(15);
	ft_init_game(&data, map);
	data.mlx_ptr = mlx_init();
	ft_parsing_map(&data, map);
	data.win_ptr = \
	mlx_new_window(data.mlx_ptr, data.width, data.height, "mlx 42");
	mlx_loop_hook(data.mlx_ptr, my_mlx_image, &data);
	mlx_hook(data.win_ptr, 17, 1L << 17, close_window, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, key_release, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
