/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 18:03:50 by cmarteau          #+#    #+#             */
/*   Updated: 2019/12/03 19:15:49 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		size;
	size_t		i;

	i = 0;
	size = ft_strlen((char *)needle);
	if (needle[i] == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0] && i + size < len + 1)
		{
			if (!ft_strncmp(&haystack[i], needle, size))
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
