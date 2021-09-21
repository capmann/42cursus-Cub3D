/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:59:34 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/15 23:54:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_atoi(const char *str, char c)
{
	unsigned int	res;
	unsigned int	i;
	unsigned int	k;

	res = 0;
	i = 0;
	k = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == 45 && str[i + 1] != 43)
	{
		k = -1;
		i++;
	}
	if (str[i] == 43)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if ((res * k) > 2147483647 && c == 'r')
		res = 2560;
	return (res * k);
}

void	ft_write_error(int a)
{
	if (a == 1)
		ft_pustr("Error\nWrong number of arguments\n");
	if (a == 4)
		ft_pustr("Error\nMap not closed\n");
	if (a == 5)
		ft_pustr("Error\nNo input for resolution\n");
	if (a == 6)
		ft_pustr("Error\nNo input for texture\n");
	if (a == 7)
		ft_pustr("Error\nProblem of file\n");
	if (a == 8)
		ft_pustr("Error\nColor issue\n");
	if (a == 10)
		ft_pustr("Error\nInvalid map\n");
	if (a == 11)
		ft_pustr("Error\nInvalid parameters\n");
	if (a == 12)
		ft_pustr("Error\nToo many parameters\n");
	if (a == 13)
		ft_pustr("Error\nMultiple assignement\n");
	if (a == 14)
		ft_pustr("Error\nWrong assignment\n");
	if (a == 15)
		ft_pustr("Error\nMissing .cub extension");
}

int	ft_parse_colors(char *line)
{
	int	i;

	i = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	while ((line[i] >= '0' && line[i] <= '9') && line[i])
		i++;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	while ((line[i] >= '0' && line[i] <= '9') && line[i])
		i++;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	if (line[i] == 0)
	{
		free(line);
		ft_error(11);
	}
	return (i);
}

void	ft_error_assignment(char *line, int i, t_cub3d *data)
{		
	if (!((line[i] == 'R' && line[i + 1] == ' ') || (line[i] == 'F' && \
		line[i + 1] == ' ') || (line[i] == 'C' && line[i + 1] == ' ') || \
		(line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'W' && \
		line[i + 1] == 'E') || (line[i] == 'S' && line[i + 1] == 'O') || \
		(line[i] == 'S' && line[i + 1] == ' ') || (line[i] == 'E' && \
		line[i + 1] == 'A') || !line[i]))
	{
		free(line);
		ft_error(14);
	}
	if ((line[i] == 'R' && line[i + 1] == ' ') || (line[i] == 'F' \
		&& line[i + 1] == ' ') || (line[i] == 'C' && line[i + 1] == ' ') || \
		(line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' \
		&& line[i + 1] == 'O') || (line[i] == 'S' && line[i + 1] == ' ') \
		|| (line[i] == 'W' && line[i + 1] == 'E') || (line[i] == 'E' && \
		line[i + 1] == 'A'))
		data->assigned++;
}

void	ft_error_tex(char *line, int a, t_cub3d *data)
{
	if (a == 6 || (a == 10 && line))
		free(line);
	ft_error(a);
	close_window(data);
}
