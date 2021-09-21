/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 21:45:13 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/03 19:31:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_search(char *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*mem;
	unsigned int	len;

	if (!s2)
		return (0);
	if (!s1 || !*s1)
	{
		mem = malloc(sizeof(char) * (ft_strlen(s2) + 1));
		if (!mem)
			return (0);
		ft_strlcpy(mem, s2, (ft_strlen(s2) + 1));
	}
	else
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		mem = malloc(sizeof(char) * (len + 1));
		if (!mem)
			return (0);
		ft_strlcpy(mem, s1, ft_strlen(s1) + 1);
		ft_strlcat(mem, s2, (ft_strlen(mem) + ft_strlen(s2) + 1));
		ft_strlcpy(mem, s1, (ft_strlen(s1) + 1));
		ft_strlcat(mem, s2, (len + 1));
	}
	free_tmp(&s1);
	return (mem);
}

int	get_next_line(int fd, char **line)
{
	static char	*tmp = NULL;
	int			ret;
	int			i;
	char		buf[BUFFER_SIZE + 1];

	ret = 1;
	while (ft_search(tmp) < 0 && (ret))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((ret == -1) || !line || BUFFER_SIZE < 1)
			return (-1);
		buf[ret] = 0;
		tmp = ft_strjoin(tmp, buf);
	}
	i = ft_search(tmp);
	if (i < 0)
		i = (int)ft_strlen(tmp);
	*line = ft_substr(tmp, 0, i);
	tmp = ft_substrf(tmp, i + 1, ft_strlen(tmp) - i - 1);
	if (ret == 0)
		return (free_tmp(&tmp));
	if (*line)
		return (1);
	return (-1);
}

int	free_tmp(char **tmp)
{
	if (*tmp)
		free(*tmp);
	*tmp = 0;
	return (0);
}
