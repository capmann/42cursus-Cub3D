/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:20:28 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/15 17:37:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_colorred(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	ft_color_check(line);
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	j = i;
	while (line[j] >= '0' && line[j] <= '9' && line[i])
		j++;
	str = ft_substr(line, i, j - i);
	if (ft_strlen(str) > 3)
	{
		free(line);
		free(str);
		ft_error(8);
		exit(0);
	}
	i = ft_atoi(str);
	free(str);
	return (i);
}

int	ft_colorgreen(char *line)
{
	int		i;
	int		j;
	int		nb;
	char	*str;

	i = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9' && line[i])
		i++;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	j = i;
	while (line[j] >= '0' && line[j] <= '9' && line[i])
		j++;
	str = ft_substr(line, i, j - i);
	ft_color_param(line, str);
	nb = ft_atoi(str);
	free(str);
	return (nb);
}

int	ft_colorblue(char *line)
{
	int		b;
	int		i;
	int		k;
	char	*str;

	i = ft_parse_colors(line);
	k = i;
	while (line[k] >= '0' && line[k] <= '9')
		k++;
	str = ft_substr(line, i, k - i);
	if (ft_strlen(str) > 3)
	{
		free(line);
		free(str);
		ft_error(8);
		exit(0);
	}
	b = ft_atoi(str);
	free(str);
	ft_nb_params(line, k);
	return (b);
}

int	ft_color(char *line)
{
	int		rgb;
	int		r;
	int		g;
	int		b;

	r = ft_colorred(line);
	g = ft_colorgreen(line);
	b = ft_colorblue(line);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
	{
		free(line);
		ft_error(8);
		exit(0);
	}
	rgb = r << 16;
	rgb += g << 8;
	rgb += b;
	return (rgb);
}
