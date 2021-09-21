/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:20:28 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/17 17:36:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_nb_params(char *line, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	j = ft_skip_space(line, j);
	if (line[j])
	{
		free(line);
		ft_error(12);
	}
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != 'R')
	{	
		while (line[i++])
			if (line[i] == ',')
				k++;
		if (k != 2)
		{
			free(line);
			ft_error(8);
			exit(0);
		}
	}
}

void	ft_check_multiple_assignement(char *line, t_cub3d *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '1' && line[i] != '0')
		ft_error_assignment(line, i, data);
	if (data->assigned > 6)
	{
		free(line);
		ft_error(13);
	}
}

void	ft_error_map2(t_cub3d *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->mapo[++i])
	{
		j = 0;
		while (data->mapo[i][j] != '\n' && data->mapo[i][j])
			j++;
		if (!(j == 0 || data->mapo[i][j - 1] == '1'))
			ft_error_tex(NULL, 4, data);
	}
	i = -1;
	while (data->mapo[++i])
	{
		j = -1;
		while (data->mapo[i][++j])
		{
			if (data->mapo[i][j] != '1' && \
				(ft_strlen(data->mapo[i - 1]) < (size_t)j + 1 || \
				ft_strlen(data->mapo[i + 1]) < (size_t)j + 1))
				ft_error_tex(NULL, 4, data);
		}
	}
}

char	*ft_check_sub(char *s)
{
	char	*memory;

	memory = malloc(1);
	if (!memory)
		return (0);
	memory[0] = 0;
	free(s);
	return (memory);
}

int	ft_check_split(char *str, int *i)
{
	int	a;

	a = *i;
	if (str[a] == '\n' && str[a - 1] == '\n')
	{
		while (str[a] == '\n')
			a++;
		if (str[a] != 0)
		{
			ft_error(4);
			*i = -1;
			return (-1);
		}
	}
	*i = a;
	return (a);
}
