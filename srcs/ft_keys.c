/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:33:16 by cmarteau          #+#    #+#             */
/*   Updated: 2021/04/03 14:32:13 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_key_delete(t_key_list *list, int keycode)
{
	t_key	*previous;
	t_key	*next;

	next = list->first;
	if (!next)
		return ;
	if (next->keycode == keycode)
	{
		list->first = next->next;
		free(next);
		return ;
	}
	while (next->keycode != keycode)
	{
		previous = next;
		next = next->next;
	}
	previous->next = next->next;
	free(next);
}

void	ft_key_addfront(t_key_list *list, t_key *new)
{
	new->next = list->first;
	list->first = new;
}

t_key	*ft_new_key(int keycode)
{
	t_key	*new;

	new = malloc(sizeof(t_key));
	if (!new)
		return (NULL);
	new->keycode = keycode;
	new->next = NULL;
	return (new);
}

int	ft_key_check(t_key_list *list, int keycode)
{
	t_key	*next;

	next = list->first;
	while (next)
	{
		if (next->keycode == keycode)
			return (1);
		next = next->next;
	}
	return (0);
}

int	key_release(int keycode, t_cub3d *data)
{
	ft_key_delete(&data->keys, keycode);
	return (keycode);
}
