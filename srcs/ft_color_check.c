/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <cmarteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:00:11 by marvin            #+#    #+#             */
/*   Updated: 2021/09/15 21:40:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_color_check(char *line)
{
	int	i;

	i = ft_skip_space(line, 0);
	while (line[++i])
	{
		if (!(line[i] == ' ' || (line[i] == ',' && line[i - 1] != 'R') || \
			(line[i] >= '0' && line[i] <= '9')))
		{
			free(line);
			ft_error(8);
			exit(0);
		}
	}
}

void	ft_color_param(char *line, char *str)
{
	if (ft_strlen(str) > 3)
	{
		free(line);
		free(str);
		ft_error(8);
		exit(0);
	}
}

void	ft_empty_line(char *line)
{
	int	i;

	i = ft_skip_space(line, 0);
	if (line[i] == 0 && i != 0 && i != 1)
	{
		free(line);
		ft_error(11);
	}
}
