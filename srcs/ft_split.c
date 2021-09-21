/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:47:58 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/09 02:28:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_sep(char c, char b)
{
	if (c == b)
		return (1);
	return (0);
}

static int	count_w(const char *str, char c)
{
	int	i;
	int	onoff;
	int	count;

	count = 0;
	onoff = 1;
	i = 0;
	while (str[i])
	{
		if (is_sep(str[i], c) == 1)
			onoff = 1;
		else
		{
			if (onoff == 1)
				count++;
			onoff = 0;
		}
		i++;
	}
	return (count);
}

static int	word_size(const char *str, int i, char c)
{
	int	k;

	k = 0;
	while (is_sep(str[i], c) == 0 && str[i])
	{
		i++;
		k++;
	}
	return (k);
}

static char	*fill_tab(const char *str, int i, int size)
{
	int		k;
	char	*tab;

	k = 0;
	tab = malloc(sizeof(char) * size + 1);
	if (tab == NULL)
		return (NULL);
	while (size > k)
	{
		if (str[i] == ' ')
		{
			tab[k++] = '1';
			i++;
		}
		else
			tab[k++] = str[i++];
	}
	tab[k] = '\0';
	return (tab);
}

char	**ft_split(const char *str, char c, t_cub3d *data, char *line)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * (count_w(str, c) + 2));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		if (ft_check_split((char *)str, &i) == -1)
			break ;
		if (is_sep(str[i], c) == 1)
			i++;
		else
		{
			tab[j++] = fill_tab(str, i, word_size(str, i, c));
			i += word_size(str, i, c);
		}
	}
	tab[j] = NULL;
	if (i == -1)
		ft_free_split(line, (char *)str, tab, data);
	return (tab);
}
